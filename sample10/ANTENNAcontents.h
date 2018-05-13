#pragma once

using namespace System;

public ref class ANTENNAcontents
{

private:
	double lx;//�A���e�i�G�������g�̒���
	double ly;//�A���e�i�G�������g�̕�

	int nx;//�A���e�i�G�������g�̐�
	int ny;//�A���e�i�G�������g�̐�

	double px;//�A���e�i�ʒu�i�A���e�i���W�n�j
	double py;//�A���e�i�ʒu�i�A���e�i���W�n�j
	double pz;//�A���e�i�ʒu�i�A���e�i���W�n�j

	int txrx;//����

public:
	ANTENNAcontents();

	//Lx�̃v���p�e�B
	property double Lx
	{
		double get()
		{
			return this->lx;
		}

		void set(double lx)
		{
			this->lx = lx;
		}
	}

	//Ly�̃v���p�e�B
	property double Ly
	{
		double get()
		{
			return this->ly;
		}

		void set(double ly)
		{
			this->ly = ly;
		}
	}

	//Nx�̃v���p�e�B
	property double Nx
	{
		double get()
		{
			return this->nx;
		}

		void set(double nx)
		{
			this->nx = nx;
		}
	}

	//Ny�̃v���p�e�B
	property double Ny
	{
		double get()
		{
			return this->ny;
		}

		void set(double ny)
		{
			this->ny = ny;
		}
	}

	//Px�̃v���p�e�B
	property double Px
	{
		double get()
		{
			return this->px;
		}

		void set(double px)
		{
			this->px = px;
		}
	}

	//Py�̃v���p�e�B
	property double Py
	{
		double get()
		{
			return this->py;
		}

		void set(double py)
		{
			this->py = py;
		}
	}

	//Pz�̃v���p�e�B
	property double Pz
	{
		double get()
		{
			return this->pz;
		}

		void set(double pz)
		{
			this->pz = pz;
		}
	}

	//TxRx�̃v���p�e�B
	property double TxRx
	{
		double get()
		{
			return this->txrx;
		}

		void set(double txrx)
		{
			this->txrx = txrx;
		}
	}

	//�f�[�^�̃Z�b�g
	void setData(double lx,double ly,int nx,int ny,double px,double py,double pz,int txrx);

};

