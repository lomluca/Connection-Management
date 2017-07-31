// File DLL principale.

#include "stdafx.h"

#include "ConnectionManagement.h"

using namespace System::Threading;


ConnectionManagement::UdpServerWrapper::UdpServerWrapper(Boolean incognito)
{
	io_service = new boost::asio::io_service();
	instance = new udp_server(*io_service, incognito);
	instance_tcp = new tcp_server(*io_service);
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
		if ((*it)->getIncognito() == false || i == 0) {
			Console::WriteLine("Ne ho aggiunto un altro");
			peersToRet[i++] = gcnew Host((*it)->getName(), (*it)->getProfilePhotoPath(), (*it)->getEndpoint().address().to_string());
		}	
	}
	Console::WriteLine("The array of online is: " + peersToRet->Length);
	return peersToRet;
}

ConnectionManagement::Host::Host(std::string name, std::string img_path, std::string ipAddr) {
	const char* tmp = name.c_str();
	this->name = gcnew String(tmp);
	tmp = img_path.c_str();
	this->imagePath = gcnew String(tmp);
	tmp = ipAddr.c_str();
	this->ipAddress = gcnew String(tmp);
}

String^ ConnectionManagement::Host::getName() {
	return name;
}

String^ ConnectionManagement::Host::getImagePath() {
	return imagePath;
}

String^ ConnectionManagement::Host::getIpAddress() {
	return ipAddress;
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