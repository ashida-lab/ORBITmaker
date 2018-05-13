#pragma once

using namespace System;

public ref class ANTENNAcontents
{

private:
	double lx;//アンテナエレメントの長さ
	double ly;//アンテナエレメントの幅

	int nx;//アンテナエレメントの数
	int ny;//アンテナエレメントの数

	double px;//アンテナ位置（アンテナ座標系）
	double py;//アンテナ位置（アンテナ座標系）
	double pz;//アンテナ位置（アンテナ座標系）

	int txrx;//送受

public:
	ANTENNAcontents();

	//Lxのプロパティ
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

	//Lyのプロパティ
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

	//Nxのプロパティ
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

	//Nyのプロパティ
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

	//Pxのプロパティ
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

	//Pyのプロパティ
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

	//Pzのプロパティ
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

	//TxRxのプロパティ
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

	//データのセット
	void setData(double lx,double ly,int nx,int ny,double px,double py,double pz,int txrx);

};

