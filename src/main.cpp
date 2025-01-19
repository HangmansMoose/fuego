#include "core.h"

using namespace winrt::Windows::Foundation;

int main()
{
    winrt::init_apartment();
    Uri uri(L"wss://127.0.0.1:9785");
	WebSocket websocket = {};
	websocket.ConnectSocket(uri);
	websocket.ReadSocket();
	websocket.WriteSocket(L"Test eagles");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());
	websocket.CloseSocket();
	return 0;
}
