// Copyright (c) 2023-2023, A3
//
// License: MIT

#include <string>
#include <iostream>
#include <fstream>

#include <osc\OscOutboundPacketStream.h>
#include <osc\OscReceivedElements.h>
#include <osc\OscPacketListener.h>
#include <ip\UdpSocket.h>

class OscProcess : public osc::OscPacketListener
{
	const std::string steam = "/sl/xrfb/facew/";
	const std::string a3 = "/avatar/parameters/";
	UdpTransmitSocket* sendSocket;
	UdpListeningReceiveSocket* recvSocket;

	char buffer[6144];
	osc::OutboundPacketStream sendPacket = osc::OutboundPacketStream(buffer,6144);

public:
	OscProcess(const char* ip= "127.0.0.1", int portSend = 9000, int portRecv = 9015) {
		sendSocket = new UdpTransmitSocket(IpEndpointName(ip, portSend));
		recvSocket = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, portRecv), this);
	}
	void RunUntilSigInt() {
		recvSocket->RunUntilSigInt();
	}
protected:
	virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& endpoint)
	{
		std::string addressPattern = m.AddressPattern();
		size_t pos = addressPattern.find(steam);
		if (pos != std::string::npos) {
			addressPattern.replace(pos, steam.length(), a3);
		}
		//std::cout << addressPattern;
		sendPacket << osc::BeginMessage(addressPattern.c_str());
		for (osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd();arg++) {
			switch (arg->TypeTag()) {
			case osc::FLOAT_TYPE_TAG:
			{
				float data = arg->AsFloat();
				sendPacket << data;
				//std::cout << data;
				break;
			}
			case osc::DOUBLE_TYPE_TAG:
			{
				double data = arg->AsDouble();
				sendPacket << data;
				//std::cout << data;
				break;
			}
			case osc::STRING_TYPE_TAG:
			{
				const char* data = arg->AsString();
				sendPacket << data;
				//std::cout << data;
				break;
			}
			case osc::INT32_TYPE_TAG:
			{
				osc::int32 data = arg->AsInt32();
				sendPacket << data;
				//std::cout << data;
				break;
			}
			case osc::INT64_TYPE_TAG:
			{
				osc::int64 data = arg->AsInt64();
				sendPacket << data;
				//std::cout << data;
				break;
			}
			default:
				std::cout << "Error:TYPE_TAG";
				break;
			}
		}
		sendPacket << osc::EndMessage;
		//std::cout << std::endl;
	}
	virtual void ProcessPacket(const char* data, int size, const IpEndpointName& remoteEndpoint)
	{
		sendPacket.Clear();
		sendPacket << osc::BeginBundleImmediate;

		osc::ReceivedPacket p(data, size);
		if (p.IsBundle())
			ProcessBundle(osc::ReceivedBundle(p), remoteEndpoint);
		else
			ProcessMessage(osc::ReceivedMessage(p), remoteEndpoint);

		sendPacket << osc::EndBundle;
		sendSocket->Send(sendPacket.Data(), sendPacket.Size());
	}
};

int main(int argc, char** argv)
{
	std::cout << "Face Tracker Steam OSC\n(c)A3\nhttps://twitter.com/A3_yuu" << std::endl;

	//arg
	const char *ip = "127.0.0.1";
	int portSend = 9000;
	int portRecv = 9015;

	switch (argc > 4 ? 4 : argc) {
	case 4:
		portRecv = atoi(argv[3]);
	case 3:
		portSend = atoi(argv[2]);
	case 2:
		ip = argv[1];
	default:
		break;
	}

	OscProcess listener(ip, portSend, portRecv);
	listener.RunUntilSigInt();

	return 0;
}