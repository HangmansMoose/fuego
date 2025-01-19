#include "WebSocket.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.security.cryptography.certificates.h>


using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Networking;
using namespace winrt::Windows::Security::Cryptography::Certificates;
using namespace winrt::Windows::Storage;

WebSocket::WebSocket() {
	m_streamWebSocket = Sockets::StreamWebSocket();
	m_streamWebSocket.Control().IgnorableServerCertificateErrors().Append(ChainValidationResult::Untrusted);
	m_streamWebSocket.Control().IgnorableServerCertificateErrors().Append(ChainValidationResult::InvalidName);
}

void WebSocket::WriteSocket(winrt::hstring message){
 
	std::cerr << "Writing to socket...." << std::endl;
    Streams::DataWriter dataWriter{ m_streamWebSocket.OutputStream() };
    dataWriter.WriteString(message);
    dataWriter.StoreAsync().get();
	dataWriter.FlushAsync().get();
    std::wstringstream wstringstream;
    wstringstream << L"Sending data using StreamWebSocket: " << message.size() << L" bytes" << std::endl;
  
}
void WebSocket::ConnectSocket(Uri target)
{
	
	std::cerr << "Connecting...." << std::endl;
		
	IAsyncAction connect =  m_streamWebSocket.ConnectAsync(target);
	connect.get();
		
}

IAsyncAction WebSocket::ReadSocket()
{
	const uint32_t readBuffSize = 4096;
	
	Streams::DataReader dataReader{ m_streamWebSocket.InputStream() };
	dataReader.InputStreamOptions(Streams::InputStreamOptions::Partial);
	co_await dataReader.LoadAsync(readBuffSize);
	uint32_t bytesLoaded = readBuffSize - dataReader.UnconsumedBufferLength();
	Streams::IBuffer readBuffer = dataReader.ReadBuffer(bytesLoaded);
	std::wstringstream wstringstream;
	wstringstream << L"Data received from StreamWebSocket: " << readBuffer.Length() << " bytes" << std::endl;
	m_streamWebSocket.Close(1000, L"");
	
}

void WebSocket::CloseSocket()
{
	m_streamWebSocket.Close();
}
