#include "../Source/Framework/Engine.h"
#include "Components/PlayerComponent.h"
#include "SpaceGame.h"

#include <iostream>
#include <cstdlib>
#include <vector>

union data_t
{
	int i;
	char str[6];
	bool b;
};

int main(int argc, char* argv[])
{
	data_t data;
	data.i = 10;
	std::cout << data.i << std::endl;

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	std::unique_ptr<SpaceGame> spacegame = std::make_unique<SpaceGame>(engine.get());
	spacegame->Initialize();


		while (!engine->IsQuit())
		{

			// render
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();
			engine->Update();

			spacegame->Draw(engine->GetRenderer());
			spacegame->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().EndFrame();
		}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}