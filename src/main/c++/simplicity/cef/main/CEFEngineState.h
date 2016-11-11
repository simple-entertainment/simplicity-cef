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
#ifndef CEFENGINESTATE_H
#define CEFENGINESTATE_H

#include <simplicity/scene/SceneState.h>

namespace simplicity
{
	namespace simcef
	{
		class CEFEngineState : public SceneState
		{
			public:
				void onAddComponent(Component& component) override;

				void onAddEntity(Entity& entity) override;
		};
	}
}

#endif /* CEFENGINESTATE_H */
