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
#ifndef CEFENGINE_H_
#define CEFENGINE_H_

#include <simplicity/engine/Engine.h>
#include <simplicity/rendering/Texture.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
	namespace simcef
	{
		/**
		 * <p>
		 * An engine that renders HTML to a texture using the Chromium Embedded Framework.
		 * </p>
		 */
		class CEFEngine : public Engine
		{
			public:
				CEFEngine(const Resource& htmlPage, Texture& texture);

				void advance() override;

				void onPlay() override;

				void onStop() override;

			private:
				const Resource& htmlPage;

				Texture& texture;
		};
	}
}

#endif /* CEFENGINE_H_ */
