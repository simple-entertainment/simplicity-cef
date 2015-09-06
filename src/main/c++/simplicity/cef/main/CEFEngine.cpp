/*
 * simple entertainment presents
 *      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity.
 * See the LICENSE file for the full license governing this code.
 */
#include <cef_app.h>

#include <simplicity/model/ModelFactory.h>
#include <simplicity/rendering/RenderingFactory.h>
#include <simplicity/Simplicity.h>
#include <simplicity/windowing/WindowEngine.h>

#include "CEFBrowser.h"
#include "CEFEngine.h"

using namespace std;

namespace simplicity
{
	namespace simcef
	{
		void CEFEngine::advance()
		{
			CefDoMessageLoopWork();
		}

		unique_ptr<Entity> CEFEngine::createUIEntity(const Resource& htmlPage) const
		{
			WindowEngine* windowEngine = Simplicity::getEngine<WindowEngine>();

			unique_ptr<Entity> uiEntity(new Entity);

			unique_ptr<Shader> vertexShader = RenderingFactory::createShader(Shader::Type::VERTEX, "clip");
			unique_ptr<Shader> fragmentShader = RenderingFactory::createShader(Shader::Type::FRAGMENT, "simple");
			shared_ptr<Pipeline> uiPipeline = RenderingFactory::createPipeline(move(vertexShader),
																			   nullptr,
																			   move(fragmentShader));

			shared_ptr<Texture> uiTexture =
					RenderingFactory::createTexture(nullptr, windowEngine->getWidth(),
													windowEngine->getHeight(), PixelFormat::BGRA);

			ModelFactory::Recipe recipe;
			recipe.shape = ModelFactory::Recipe::Shape::RECTANGLE;
			recipe.dimensions = Vector3(2.0f, 2.0f, 0.0f);
			unique_ptr<Mesh> uiQuad = ModelFactory::cookMesh(recipe);
			uiQuad->getBuffer()->setPipeline(uiPipeline);
			uiQuad->setTexture(uiTexture);
			uiEntity->addUniqueComponent(move(uiQuad));

			unique_ptr<Component> uiBrowser(new CEFBrowser(htmlPage, uiTexture));
			uiEntity->addUniqueComponent(move(uiBrowser));

			return move(uiEntity);
		}

		void CEFEngine::onAddEntity(Entity& entity)
		{
			for (CEFBrowser* browser : entity.getComponents<CEFBrowser>())
			{
				browser->load(entity);
			}
		}

		void CEFEngine::onPlay()
		{
			CefSettings settings;
			CefString(&settings.browser_subprocess_path).FromASCII("lib/simplicity-cef-subprocess");
			CefString(&settings.locales_dir_path).FromASCII("assets/cef/locales");
			CefString(&settings.resources_dir_path).FromASCII("assets/cef");

			CefInitialize(CefMainArgs(0, nullptr), settings, nullptr, nullptr);
		}

		void CEFEngine::onStop()
		{
			CefShutdown();
		}
	}
}
