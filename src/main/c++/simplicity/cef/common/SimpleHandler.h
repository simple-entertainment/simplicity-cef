/*
 * Copyright © 2015 Simple Entertainment Limited
 *
 * This file is part of The Simplicity Engine.
 *
 * The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef SIMPLE_HANDLER_H_
#define SIMPLE_HANDLER_H_

#include <list>

#include <cef_client.h>

namespace simplicity
{
    namespace simcef
    {
        class SimpleHandler : public CefClient, public CefDisplayHandler, public CefLifeSpanHandler,
                              public CefLoadHandler
        {
            public:
                SimpleHandler();

                ~SimpleHandler();

                // Provide access to the single global instance of this object.
                static SimpleHandler* GetInstance();

                // CefClient methods:
                CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
                return this;
                }
                CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
                return this;
                }
                CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
                return this;
                }

                // CefDisplayHandler methods:
                void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

                // CefLifeSpanHandler methods:
                void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
                bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
                void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

                // CefLoadHandler methods:
                void OnLoadError(CefRefPtr<CefBrowser> browser,
                CefRefPtr<CefFrame> frame,
                ErrorCode errorCode,
                const CefString& errorText,
                const CefString& failedUrl) OVERRIDE;

                // Request that all existing browser windows close.
                void CloseAllBrowsers(bool force_close);

                bool IsClosing() const { return is_closing_; }

            private:
                // List of existing browser windows. Only accessed on the CEF UI thread.
                typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
                BrowserList browser_list_;

                bool is_closing_;

                IMPLEMENT_REFCOUNTING(SimpleHandler);
        };
    }
}

#endif  /* SIMPLE_HANDLER_H_ */
