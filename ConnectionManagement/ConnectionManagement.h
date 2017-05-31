// ConnectionManagement.h

#pragma once
#include "c:\Progetto\Progetto\udp_server.h"


using namespace System;

namespace ConnectionManagement {

	public ref class Host
	{
	public:
		Host(std::string name, std::string img_path);
		String^ getName();
		String^ getImagePath();


	private:
		String^ name;
		String^ imagePath;

	};

	public ref class UdpServerWrapper
	{
		// TODO: aggiungere qui i metodi per la classe.
	public:
		UdpServerWrapper(Boolean incognito);
		void setIncognito(Boolean value);
		Boolean getIncognito();
		void startIOServ();
		void stopIOServ();
		array<Host^>^ getConnectedHosts();

	private:
		udp_server* instance;
		boost::asio::io_service* io_service;

	};
}
