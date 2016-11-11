/*      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity. See the LICENSE file for the full license governing this code.
 */
#include <algorithm>

#include "CEFBrowser.h"
#include "CEFEngineState.h"

using namespace std;

namespace simplicity
{
    namespace simcef
    {
        void CEFEngineState::onAddComponent(Component& component)
        {
            CEFBrowser* browser = dynamic_cast<CEFBrowser*>(&component);
            if (browser != nullptr)
            {
                browser->load();
            }
        }

        void CEFEngineState::onAddEntity(Entity& entity)
        {
            for (CEFBrowser* browser : entity.getComponents<CEFBrowser>())
            {
                browser->load();
            }
        }
    }
}
