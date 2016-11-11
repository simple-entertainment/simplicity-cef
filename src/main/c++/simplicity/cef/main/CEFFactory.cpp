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

#include <simplicity/model/Model.h>
#include <simplicity/model/ModelFactory.h>
#include <simplicity/rendering/RenderingFactory.h>
#include <simplicity/Simplicity.h>
#include <simplicity/windowing/WindowEngine.h>

#include "CEFBrowser.h"
#include "CEFFactory.h"

using namespace std;

namespace simplicity
{
    namespace simcef
    {
        namespace CEFFactory
        {
            unique_ptr<Entity> createUIEntity(const Resource& htmlPage)
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
                shared_ptr<Mesh> uiQuad = ModelFactory::cookMesh(recipe);
                uiQuad->getBuffer()->setPipeline(uiPipeline);
                unique_ptr<Model> uiModel(new Model);
                uiModel->setMesh(uiQuad);
                uiModel->setTexture(uiTexture);
                uiEntity->addComponent(move(uiModel));

                unique_ptr<Component> uiBrowser(new CEFBrowser(htmlPage, uiTexture));
                uiEntity->addComponent(move(uiBrowser));

                return move(uiEntity);
            }
        }
    }
}
