#pragma once

// This include is purely for clang, MSVC compiler is not bothered by it.  
#include <guiddef.h>
// These are standard includes
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Storage.streams.h>

using namespace winrt::Windows::Networking;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Foundation;


class WebSocket {
private:
	Sockets::StreamWebSocket m_streamWebSocket;
	
public:
	WebSocket();
	~WebSocket() = default;
	// Create the socket and then attach The input and output streams
	void ConnectSocket(Uri target);
	IAsyncAction ReadSocket();
	void WriteSocket(winrt::hstring);
	void CloseSocket();
};
