#include "../Source/Framework/Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	//auto a = Factory::Instance().Create("Actor");

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("text.txt", s);
	std::cout << s << std::endl;

	rapidjson::Document document;
	Json::Load("text.txt", document);
	
	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);

	std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;


	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Orange.png", engine->GetRenderer());

		res_t<Font> font = ResourceManager::Instance().Get<Font>("QuirkyRobot.ttf", 36);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hi!", { 1, 1, 0, 1 });

		Transform t{ { 30, 30 } };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->setTransform(t);
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();
			//engine->GetPS().Draw(engine->GetRenderer());

			//engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 200, 200);

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}