#pragma once
#include "Singleton.h"

#include <fstream>
#include <iostream>

#ifdef new
#pragma push_macro("new")
#undef new
#endif

#include "json.hpp"

#ifdef new
#pragma pop_macro("new")
#endif

using json = nlohmann::json;

class GameObject;
class Ui;

class UiLayoutManager
{
public:

	template<typename T>
	void Save(const string& filename, const vector<T*>& uiList)
	{
		json j = json::array();

		for (auto obj : uiList)
		{
			if (!obj)
				continue;

			json item;
			wstring s = obj->GetKey();
			string name = string(s.begin(), s.end());

			item["name"] = name;
			item["x"] = obj->GetOrAddTransform()->GetPosition().x;
			item["y"] = obj->GetOrAddTransform()->GetPosition().y;
			item["z"] = obj->GetOrAddTransform()->GetPosition().z;

			j.push_back(item);
		}

		ofstream file(filename);
		file << j.dump(4);	// 가독성을 위해 4칸 들여쓰기
		cout << "[DEBUG] UI 레이아웃 저장 완료. 파일명:"<< filename << endl;
		file.close();
	}

	template<typename T>
	void Load(const string& filename, const vector<T*>& uiList)
	{
        ifstream file(filename);

        if (!file.is_open())
            return;

        json j;
        file >> j;

        for (auto& item : j)
        {
			if (!item.contains("name") || !item["name"].is_string())
				continue;

            string nameStr = item["name"];
            wstring name(nameStr.begin(), nameStr.end());

            int x = item["x"];
            int y = item["y"];
            int z = item["z"];

            for (auto obj : uiList)
            {
                if (obj->GetKey() == name)
                {
					obj->GetOrAddTransform()->SetPosition(Vec3(x, y, z));
                }
            }
        }
        file.close();
	}

private:

};

