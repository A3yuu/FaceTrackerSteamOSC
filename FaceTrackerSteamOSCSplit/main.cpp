// Copyright (c) 2023-2024, A3
//
// License: MIT

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <thread>

#include <osc\OscOutboundPacketStream.h>
#include <osc\OscReceivedElements.h>
#include <osc\OscPacketListener.h>
#include <ip\UdpSocket.h>

const std::map<std::string, int> addressMap = {
	{"/avatar/parameters/BrowLowererL",	       0} ,
	{"/avatar/parameters/BrowLowererR",	       1} ,
	{"/avatar/parameters/CheekPuffL",		   2} ,
	{"/avatar/parameters/CheekPuffR",		   3} ,
	{"/avatar/parameters/CheekRaiserL",	       4} ,
	{"/avatar/parameters/CheekRaiserR",	       5} ,
	{"/avatar/parameters/CheekSuckL",		   6} ,
	{"/avatar/parameters/CheekSuckR",		   7} ,
	{"/avatar/parameters/ChinRaiserB",		   8} ,
	{"/avatar/parameters/ChinRaiserT",		   9} ,
	{"/avatar/parameters/DimplerL",		       10} ,
	{"/avatar/parameters/DimplerR",		       11} ,
	{"/avatar/parameters/EyesClosedL",		   12} ,
	{"/avatar/parameters/EyesClosedR",		   13} ,
	{"/avatar/parameters/EyesLookDownL",	   14} ,
	{"/avatar/parameters/EyesLookDownR",	   15} ,
	{"/avatar/parameters/EyesLookLeftL",	   16} ,
	{"/avatar/parameters/EyesLookLeftR",	   17} ,
	{"/avatar/parameters/EyesLookRightL",	   18} ,
	{"/avatar/parameters/EyesLookRightR",	   19} ,
	{"/avatar/parameters/EyesLookUpL",		   20} ,
	{"/avatar/parameters/EyesLookUpR",		   21} ,
	{"/avatar/parameters/InnerBrowRaiserL",    22} ,
	{"/avatar/parameters/InnerBrowRaiserR",    23} ,
	{"/avatar/parameters/JawDrop",			   24} ,
	{"/avatar/parameters/JawSidewaysLeft",	   25} ,
	{"/avatar/parameters/JawSidewaysRight",    26} ,
	{"/avatar/parameters/JawThrust",		   27} ,
	{"/avatar/parameters/LidTightenerL",	   28} ,
	{"/avatar/parameters/LidTightenerR",	   29} ,
	{"/avatar/parameters/LipCornerDepressorL", 30} ,
	{"/avatar/parameters/LipCornerDepressorR", 31} ,
	{"/avatar/parameters/LipCornerPullerL",    32} ,
	{"/avatar/parameters/LipCornerPullerR",    33} ,
	{"/avatar/parameters/LipFunnelerLB",	   34} ,
	{"/avatar/parameters/LipFunnelerLT",	   35} ,
	{"/avatar/parameters/LipFunnelerRB",	   36} ,
	{"/avatar/parameters/LipFunnelerRT",	   37} ,
	{"/avatar/parameters/LipPressorL",		   38} ,
	{"/avatar/parameters/LipPressorR",		   39} ,
	{"/avatar/parameters/LipPuckerL",		   40} ,
	{"/avatar/parameters/LipPuckerR",		   41} ,
	{"/avatar/parameters/LipStretcherL",	   42} ,
	{"/avatar/parameters/LipStretcherR",	   43} ,
	{"/avatar/parameters/LipSuckLB",		   44} ,
	{"/avatar/parameters/LipSuckLT",		   45} ,
	{"/avatar/parameters/LipSuckRB",		   46} ,
	{"/avatar/parameters/LipSuckRT",		   47} ,
	{"/avatar/parameters/LipTightenerL",	   48} ,
	{"/avatar/parameters/LipTightenerR",	   49} ,
	{"/avatar/parameters/LipsToward",		   50} ,
	{"/avatar/parameters/LowerLipDepressorL",  51} ,
	{"/avatar/parameters/LowerLipDepressorR",  52} ,
	{"/avatar/parameters/MouthLeft",		   53} ,
	{"/avatar/parameters/MouthRight",		   54} ,
	{"/avatar/parameters/NoseWrinklerL",	   55} ,
	{"/avatar/parameters/NoseWrinklerR",	   56} ,
	{"/avatar/parameters/OuterBrowRaiserL",    57} ,
	{"/avatar/parameters/OuterBrowRaiserR",    58} ,
	{"/avatar/parameters/UpperLidRaiserL",	   59} ,
	{"/avatar/parameters/UpperLidRaiserR",	   60} ,
	{"/avatar/parameters/UpperLipRaiserL",	   61} ,
	{"/avatar/parameters/UpperLipRaiserR",	   62} ,
	{"/avatar/parameters/TongueTipInterdental",63} ,
	{"/avatar/parameters/TongueTipAlveolar",   64} ,
	{"/avatar/parameters/TongueOut",           65} ,
	{"/avatar/parameters/TongueRetreat",       66} ,
	{"/avatar/parameters/BackDorsalVelar",     67} ,
	{"/avatar/parameters/MidDorsalPalate",     68} ,
	{"/avatar/parameters/FrontDorsalPalate",   69} ,
};
const std::string address[] = {
	"/avatar/parameters/BrowLowererL",	       
	"/avatar/parameters/BrowLowererR",	       
	"/avatar/parameters/CheekPuffL",		   
	"/avatar/parameters/CheekPuffR",		   
	"/avatar/parameters/CheekRaiserL",	       
	"/avatar/parameters/CheekRaiserR",	       
	"/avatar/parameters/CheekSuckL",		   
	"/avatar/parameters/CheekSuckR",		   
	"/avatar/parameters/ChinRaiserB",		   
	"/avatar/parameters/ChinRaiserT",		   
	"/avatar/parameters/DimplerL",		       
	"/avatar/parameters/DimplerR",		       
	"/avatar/parameters/EyesClosedL",		   
	"/avatar/parameters/EyesClosedR",		   
	"/avatar/parameters/EyesLookDownL",	   
	"/avatar/parameters/EyesLookDownR",	   
	"/avatar/parameters/EyesLookLeftL",	   
	"/avatar/parameters/EyesLookLeftR",	   
	"/avatar/parameters/EyesLookRightL",	   
	"/avatar/parameters/EyesLookRightR",	   
	"/avatar/parameters/EyesLookUpL",		   
	"/avatar/parameters/EyesLookUpR",		   
	"/avatar/parameters/InnerBrowRaiserL",    
	"/avatar/parameters/InnerBrowRaiserR",    
	"/avatar/parameters/JawDrop",			   
	"/avatar/parameters/JawSidewaysLeft",	   
	"/avatar/parameters/JawSidewaysRight",    
	"/avatar/parameters/JawThrust",		   
	"/avatar/parameters/LidTightenerL",	   
	"/avatar/parameters/LidTightenerR",	   
	"/avatar/parameters/LipCornerDepressorL", 
	"/avatar/parameters/LipCornerDepressorR", 
	"/avatar/parameters/LipCornerPullerL",    
	"/avatar/parameters/LipCornerPullerR",    
	"/avatar/parameters/LipFunnelerLB",	   
	"/avatar/parameters/LipFunnelerLT",	   
	"/avatar/parameters/LipFunnelerRB",	   
	"/avatar/parameters/LipFunnelerRT",	   
	"/avatar/parameters/LipPressorL",		   
	"/avatar/parameters/LipPressorR",		   
	"/avatar/parameters/LipPuckerL",		   
	"/avatar/parameters/LipPuckerR",		   
	"/avatar/parameters/LipStretcherL",	   
	"/avatar/parameters/LipStretcherR",	   
	"/avatar/parameters/LipSuckLB",		   
	"/avatar/parameters/LipSuckLT",		   
	"/avatar/parameters/LipSuckRB",		   
	"/avatar/parameters/LipSuckRT",		   
	"/avatar/parameters/LipTightenerL",	   
	"/avatar/parameters/LipTightenerR",	   
	"/avatar/parameters/LipsToward",		   
	"/avatar/parameters/LowerLipDepressorL",  
	"/avatar/parameters/LowerLipDepressorR",  
	"/avatar/parameters/MouthLeft",		   
	"/avatar/parameters/MouthRight",		   
	"/avatar/parameters/NoseWrinklerL",	   
	"/avatar/parameters/NoseWrinklerR",	   
	"/avatar/parameters/OuterBrowRaiserL",    
	"/avatar/parameters/OuterBrowRaiserR",    
	"/avatar/parameters/UpperLidRaiserL",	   
	"/avatar/parameters/UpperLidRaiserR",	   
	"/avatar/parameters/UpperLipRaiserL",	   
	"/avatar/parameters/UpperLipRaiserR",	   
	"/avatar/parameters/TongueTipInterdental",
	"/avatar/parameters/TongueTipAlveolar",   
	"/avatar/parameters/TongueOut",           
	"/avatar/parameters/TongueRetreat",       
	"/avatar/parameters/BackDorsalVelar",     
	"/avatar/parameters/MidDorsalPalate",     
	"/avatar/parameters/FrontDorsalPalate",   
};
const char* faceCountAddress = "/avatar/parameters/faceCount";
char faceParameterAddress[] = "/avatar/parameters/face00";
int faceParameterAddressLen = sizeof(faceParameterAddress);
const int FACE_MAX = 70;
const int SPLIT_NUM = 24;
const int SPLIT = 3;

const char* eyeCenterVecFullAddress = "/tracking/eye/CenterVecFull";
const char* eyeEyesClosedAmountAddress = "/tracking/eye/EyesClosedAmount";


class OscProcess : public osc::OscPacketListener
{
	const std::string steam = "/sl/xrfb/facew/";
	const std::string a3 = "/avatar/parameters/";
	UdpTransmitSocket* sendSocket;
	UdpListeningReceiveSocket* recvSocket;

	char buffer[6144];
	osc::OutboundPacketStream sendPacket = osc::OutboundPacketStream(buffer,6144);

	int faceCount = 0;
	bool procing = false;

	float faceData[FACE_MAX];
	float eyeCenterVecFull[3] = { 0,0,0 };
	float eyeEyesClosedAmount = 0;
public:
	OscProcess(const char* ip= "127.0.0.1", int portSend = 9000, int portRecv = 9015) {
		sendSocket = new UdpTransmitSocket(IpEndpointName(ip, portSend));
		recvSocket = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, portRecv), this);
	}
	void RunUntilSigInt() {
		recvSocket->RunUntilSigInt();
	}
	void Run() {
		recvSocket->Run();
	}
	void SendConflictPrevention() {
		sendPacket.Clear();
		sendPacket << osc::BeginBundleImmediate;
		sendPacket << osc::BeginMessage(faceCountAddress);
		sendPacket << 0;
		sendPacket << osc::EndMessage;
		sendPacket << osc::EndBundle;
		sendSocket->Send(sendPacket.Data(), sendPacket.Size());
	}
	void SendPacket() {
		//パケット作成
		sendPacket.Clear();
		sendPacket << osc::BeginBundleImmediate;

		//顔データは分割
		sendPacket << osc::BeginMessage(faceCountAddress);
		sendPacket << faceCount + 1;
		sendPacket << osc::EndMessage;
		for (int i = 0;i < SPLIT_NUM && i + SPLIT_NUM * faceCount < FACE_MAX;i++)
		{
			faceParameterAddress[faceParameterAddressLen - 2] = '0' + i % 10;
			faceParameterAddress[faceParameterAddressLen - 3] = '0' + i / 10;
			sendPacket << osc::BeginMessage(faceParameterAddress);
			sendPacket << faceData[i + SPLIT_NUM * faceCount];
			sendPacket << osc::EndMessage;
		}
		if (++faceCount >= SPLIT) {
			faceCount = 0;
		}

		//目データ
		sendPacket << osc::BeginMessage(eyeCenterVecFullAddress);
		sendPacket << eyeCenterVecFull[0] << eyeCenterVecFull[1] << eyeCenterVecFull[2];
		sendPacket << osc::EndMessage;
		//sendPacket << osc::BeginMessage(eyeEyesClosedAmountAddress);
		//sendPacket << eyeEyesClosedAmount;
		//sendPacket << osc::EndMessage;

		//パケット送信
		sendPacket << osc::EndBundle;
		sendSocket->Send(sendPacket.Data(), sendPacket.Size());
	}
protected:

	virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& endpoint)
	{
		std::string addressPattern = m.AddressPattern();

		//Face
		size_t pos = addressPattern.find(steam);
		if (pos != std::string::npos) {
			addressPattern.replace(pos, steam.length(), a3);
			auto iter = addressMap.find(addressPattern);
			if (iter != end(addressMap)) {
				faceData[iter->second] = m.ArgumentsBegin()->AsFloat();
				return;
			}
		}
		//Eye
		if (!strcmp(addressPattern.c_str(), eyeCenterVecFullAddress)) {
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			for (int i = 0;i < 3 && arg != m.ArgumentsEnd();i++) {
				eyeCenterVecFull[i] = arg->AsFloat();
				arg++;
			}
		}
		if (!strcmp(addressPattern.c_str(), eyeEyesClosedAmountAddress)) {
			eyeEyesClosedAmount = m.ArgumentsBegin()->AsFloat();
		}
	}
	virtual void ProcessPacket(const char* data, int size, const IpEndpointName& remoteEndpoint)
	{
		//解析開始
		osc::ReceivedPacket p(data, size);
		if (p.IsBundle())
			ProcessBundle(osc::ReceivedBundle(p), remoteEndpoint);
		else
			ProcessMessage(osc::ReceivedMessage(p), remoteEndpoint);
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
	std::thread lt([&listener]() { listener.Run();});
	//listener.Run();

	while (true) {
		_sleep(4);
		listener.SendConflictPrevention();
		_sleep(4);
		listener.SendPacket();
	}

	return 0;
}