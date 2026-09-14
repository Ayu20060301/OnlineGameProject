#pragma once


#include "Client.h"


class Host : public Client
{
public:
	Host();
	virtual ~Host();

private:
	void StartNetwork() override;
	void UpdateWaiting() override;
	void DrawWaiting() override;
private:
	IPDATA m_ClientIP;
};
