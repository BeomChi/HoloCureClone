//#pragma once
//#include <vector>
//#include <functional>
//#include <cstdint>
//#include <algorithm>
//
//using namespace std;
//
//// Signal 클래스는 이벤트 시스템을 구현하기 위한 클래스
//struct ISignal
//{
//    virtual ~ISignal() {};
//	virtual void Disconnect(size_t id) = 0;
//};
//
//struct Connection
//{
//    struct Node
//    {
//        size_t id;
//        ISignal* owner;
//        explicit Node(size_t i, ISignal* o) : id(i), owner(o) {}
//    };
//
//    Connection() { cout << "[DEBUG] Connection 생성 (default)" << endl; }
//    Connection(const Connection&) = delete;
//    Connection& operator=(const Connection&) = delete;
//
//    // move ctor / move assign 
//    Connection(Connection&&) noexcept { cout << "[DEBUG] Connection 이동 생성" << endl; }
//    Connection& operator=(Connection&&) noexcept {
//        cout << "[DEBUG] Connection 이동 대입" << endl;
//        return *this;
//    }
//
//    explicit Connection(Node* n) : _node(n) {}
//
//    void Disconnect()
//    {
//        if (_node && _node->owner)          // 아직 Signal이 살아 있다면
//        {
//            cout << "[DEBUG] Disconnect 호출됨. owner: " << _node->owner << ", id: " << _node->id << endl;
//            _node->owner->Disconnect(_node->id);
//            _node->owner = nullptr;
//        }
//    }
//    ~Connection() 
//    {
//        cout << "[DEBUG] Connection 소멸됨" << endl;
//        //cout << "[DEBUG] ~Connection() 호출됨. Node->owner: " << _node->owner << endl;
//        Disconnect();
//    }
//
//    Node* GetNode() const { return _node; }
//
//private:
//    Node* _node = nullptr;                  // Node 소유권 X
//};
//
///* ───────────────────── Signal 본체 ───────────────────────────── */
//template<typename... Args>
//class Signal : public ISignal
//{
//public:
//    using Callback = function<void(Args...)>;
//    Signal() = default;
//    Signal(const Signal&) = delete;
//    Signal& operator=(const Signal&) = delete;
//
//    // += 구독 
//    Connection operator+=(Callback&& cb)
//    {
//        size_t id = _nextId++;
//
//        cout << "[DEBUG] 등록 전 콜백 수: " << _callbacks.size() << endl;
//        _callbacks.emplace_back(id, move(cb));
//        cout << "[DEBUG] 등록 후 콜백 수: " << _callbacks.size() << endl;
//
//        // Node를 heap에 생성 → Signal이 소유
//        auto* node = new Connection::Node{ id, this };
//        _nodes.push_back(node);
//        cout << "[DEBUG] 이벤트 등록됨. id: " << node->id << ", owner: " << node->owner << endl;
//
//        // Connection은 Node*만 보유 
//        return Connection(node);
//    }
//
//    // () 발행 
//    void operator()(Args... args) const
//    {
//        cout << "[DEBUG] Signal 발행됨" << endl;
//        cout << "[DEBUG] Signal 발행됨. 콜백 수: " << _callbacks.size() << endl;
//        for (auto& [id, fn] : _callbacks)
//        {
//            cout << "[DEBUG] 콜백 실행. id: " << id << ", 유효: " << (bool)fn << endl;
//            if (fn)
//                fn(args...);
//        }
//    }
//
//    // Signal 파괴 시 Node 메모리 해제 
//    ~Signal() override
//    {
//        for (auto* n : _nodes)     // Connection이 먼저 파괴돼도 여기서 해제
//            delete n;
//
//        _nodes.clear();
//        _callbacks.clear();
//    }
//
//private:            // ISignal 구현 → 콜백 제거 
//    void Disconnect(size_t id) override
//    {
//        auto it = remove_if(_callbacks.begin(), _callbacks.end(),
//            [id](auto& p) { return p.first == id; });
//
//        _callbacks.erase(it, _callbacks.end());
//    }
//
//    vector<pair<size_t, Callback>> _callbacks; // (id,fn)
//    vector<Connection::Node*> _nodes;                    // Node 소유
//    size_t _nextId = 0;
//};

#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>


struct ISignal
{
    virtual void Disconnect(std::size_t id) = 0;
};


struct Connection
{
    // 내부 공유 노드 : id 와 owner 포인터를 보관
    struct Node
    {
        size_t id;
        ISignal* owner;
        Node(size_t i, ISignal* o) : id(i), owner(o) {}
    };

    // Move‑only semantics 
    Connection() = default;
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    // Construct with id + owner
    explicit Connection(size_t id, ISignal* o)
        : _node(make_shared<Node>(id, o)) {
    }

    Connection(Connection&&) noexcept = default;
    Connection& operator=(Connection&&) noexcept = default;

    /* 연결 끊기 */
    void Disconnect()
    {
        if (_node && _node->owner)
        {
            _node->owner->Disconnect(_node->id);
            _node->owner = nullptr;
        }
    }
    ~Connection() { Disconnect(); }

    // 내부 노드 포인터를 Signal 에서 접근할 수 있도록 공개
    shared_ptr<Node> GetNode() const { return _node; }

private:
    shared_ptr<Node> _node;
};


template <typename... Args>
class Signal : public ISignal
{
public:
    using Callback = function<void(Args...)>;

    // +=  구독
    Connection operator+=(Callback&& cb)
    {
        const size_t id = _nextId++;
        _slots.emplace_back(id, std::move(cb));

        Connection conn{ id, this };               // 실제 Connection 생성
        _connNodes.emplace_back(conn.GetNode()); // weak_ptr 저장
        return conn;                             // NRVO + move
    }

    //  ()  발행
    void operator()(Args... args) const
    {
        for (const auto& [id, fn] : _slots)
            if (fn) 
                fn(args...);
    }

    // Signal 파괴 시 남은 Connection 의 owner 포인터 안가리키게 하기
    ~Signal()
    {
        for (auto& wnode : _connNodes)
            if (auto node = wnode.lock())
                node->owner = nullptr;           // dangling 방지
    }

private:
    /* ISignal 인터페이스 구현 */
    void Disconnect(size_t id) override
    {
        auto it = remove_if(_slots.begin(), _slots.end(),
            [id](const auto& p) { return p.first == id; });
        _slots.erase(it, _slots.end());
    }

private:
    vector<pair<size_t, Callback>> _slots;          // (id, fn)
    vector<weak_ptr<Connection::Node>>  _connNodes;      // 연결 노드
    size_t _nextId = 0;
};
