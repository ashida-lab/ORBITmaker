#include "ANTENNAcontents.h"


ANTENNAcontents::ANTENNAcontents()
{
}

//�f�[�^�̃Z�b�g
void ANTENNAcontents::setData(double lx, double ly, int nx, int ny, double px, double py, double pz, int txrx)
{
	this->lx = lx;
	this->ly = ly;
	this->nx = nx;
	this->ny = ny;
	this->px = px;
	this->py = py;
	this->pz = pz;
	this->txrx = txrx;
}