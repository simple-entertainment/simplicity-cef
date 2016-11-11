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
#ifndef CEFFACTORY_H
#define CEFFACTORY_H

#include <memory>

#include <simplicity/entity/Entity.h>
#include <simplicity/resources/Resource.h>

namespace simplicity
{
    namespace simcef
    {
        namespace CEFFactory
        {
            std::unique_ptr<Entity> createUIEntity(const Resource& htmlPage);
        }
    }
}

#endif /* CEFFACTORY_H */
