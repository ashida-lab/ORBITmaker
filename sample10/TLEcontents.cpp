#include "TLEcontents.h"


TLEcontents::TLEcontents()
{
}

//�f�[�^�̃Z�b�g
void TLEcontents::setData(String^ name,String^ l1,String^ l2)
{
	this->name = name;
	this->l1 = l1;
	this->l2 = l2;
}