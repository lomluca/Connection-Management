// File DLL principale.

#include "stdafx.h"

#include "ConnectionManagement.h"

using namespace System::Threading;


ConnectionManagement::UdpServerWrapper::UdpServerWrapper(Boolean incognito)
{
	io_service = new boost::asio::io_service();
	instance = new udp_server(*io_service, incognito);
	tcp_server serverTCP(*io_service);
}

void ConnectionManagement::UdpServerWrapper::startIOServ() {
	instance->setIOLock();
	io_service->run();
	instance->setIOUnlock();
	
}


array<ConnectionManagement::Host^>^ ConnectionManagement::UdpServerWrapper::getConnectedHosts() {
	std::list<Peer*> peers = instance->getConnectedPeer();
	Console::WriteLine("THERE ARE " + peers.size());
	array<ConnectionManagement::Host^>^ peersToRet = gcnew array<ConnectionManagement::Host^>(peers.size());
	int i = 0;
	for (auto it = peers.begin(); it != peers.end(); it++) {
		std::string name = (*it)->getName();
		std::cout << name << std::endl;
		peersToRet[i++] = gcnew Host((*it)->getName(), (*it)->getProfilePhotoPath());
		Console::WriteLine(peersToRet[i-1]->getName());
	}
	return peersToRet;
}

ConnectionManagement::Host::Host(std::string name, std::string img_path) {
	const char* tmp = name.c_str();
	this->name = gcnew String(tmp);
	tmp = img_path.c_str();
	this->imagePath = gcnew String(tmp);
}

String^ ConnectionManagement::Host::getName() {
	return name;
}

String^ ConnectionManagement::Host::getImagePath() {
	return imagePath;
}

void ConnectionManagement::UdpServerWrapper::stopIOServ() {
	instance->handle_stop_all(*io_service);
}

Boolean ConnectionManagement::UdpServerWrapper::getIncognito() {
	return instance->getIncognito();
}

void ConnectionManagement::UdpServerWrapper::setIncognito(Boolean value) {
	instance->setIncognito(value);
}