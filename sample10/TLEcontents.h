#pragma once

using namespace System;

public ref class TLEcontents
{
private:
	System::String^ name;
	System::String^ l1;
	System::String^ l2;

public:
	TLEcontents();

	//name�̃v���p�e�B
	property System::String^ Name
	{
		System::String^ get()
		{
			return this->name;
		}

		void set(System::String^ name)
		{
			this->name = name;
		}
	}

	//l1�̃v���p�e�B
	property System::String^ L1
	{
		System::String^ get()
		{
			return this->l1;
		}

		void set(System::String^ l1)
		{
			this->l1 = l1;
		}
	}

	//l1�̃v���p�e�B
	property System::String^ L2
	{
		System::String^ get()
		{
			return this->l2;
		}

		void set(System::String^ l2)
		{
			this->l2 = l2;
		}
	}

	//�f�[�^�̃Z�b�g
	void setData(System::String^ name, System::String^ l1, System::String^ l2);

};

