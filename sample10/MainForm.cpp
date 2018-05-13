#include <stdio.h>

#include "MainForm.h"
#include "OpenGLSimpleAdapter.h"

#include <GL/glut.h>

using namespace sample10;  //  <--�@�����ɂ̓v���W�F�N�g��������
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

GLUquadricObj *Sphere;
GLUquadricObj *Sattelite;
GLuint tex;
double theta[3] = { 0.0, 0.0, 0.0 };
double angle[3] = { 0.0, 0.0, 0.0 };
static int axis = 1;
float scale_facter = 3.0;
System::Drawing::Point startPoint;

/*
** ����
*/
static const GLfloat lightpos[] = { 20.0, 0.0, 0.0, 0.0 }; /* �ʒu�@�@�@ */
static const GLfloat lightcol[] = { 1.0, 1.0, 1.0, 1.0 }; /* ���ڌ����x */
static const GLfloat lightamb[] = { 0.1, 0.1, 0.1, 1.0 }; /* �������x */

/*
** �e�N�X�`��
*/
static const char texture1[] = "C:\\Users\\ashiy\\Pictures\\land_ocean_ice_8192.png"; /* �e�N�X�`���t�@�C���� */


[sample10::STAThreadAttribute]
int main(int argc, char *argv[])
{
	sample10::MainForm ^fm = gcnew sample10::MainForm();
	fm->ShowDialog();
	return 0;
}

Bitmap^ MainForm::mat2bmp(cv::Mat img)
{
	cv::Mat out;
	if (img.channels() == 1){

		cv::Mat in[] = { img, img, img };//R G B
		out = cv::Mat(img.cols, img.rows, CV_8UC3);

		cv::merge(in, 3, out);
	}
	else{
		out = img.clone();
	}

	const int aligneCol = static_cast<int>(cv::alignSize(out.cols, 4));
	cv::Mat t_mat = cv::Mat(out.rows, aligneCol, out.type());

	cv::Mat roi_mat2 = cv::Mat(t_mat, cv::Rect(0, 0, out.cols, out.rows));

	out.copyTo(roi_mat2);
	Bitmap^ inter_bmp = gcnew Bitmap(roi_mat2.cols, roi_mat2.rows, roi_mat2.step,
		PixelFormat::Format24bppRgb, IntPtr(roi_mat2.ptr()));

	Bitmap^ bmp = gcnew Bitmap(inter_bmp);

	return bmp;
}

System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	GLAdapter = gcnew OpenGLSimpleAdapter(GetDC((HWND)earthPanel->Handle.ToPointer()));

	readTexture();

	panelRefresh();
}

System::Void MainForm::earthPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	panelRefresh();
}

System::Void MainForm::panelRefresh(void)
{
	static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
	static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
	static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
	static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };

	GLAdapter->BeginRender();
	{
		// Initialize
		glClearColor(0, 0, 0, 0);
		glMatrixMode(GL_PROJECTION);
		int w = earthPanel->Width;
		int h = earthPanel->Height;

		glViewport(0, 0, w, h);

		// Drawing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		//����p,�A�X�y�N�g��(�E�B���h�E�̕�/����),�`�悷��͈�(�ł��߂�����,�ł���������)
		gluPerspective(30.0, (double)w / (double)h, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//���_�̐ݒ�
		gluLookAt(0.0, 0.0, 20.0, //�J�����̍��W
			0.0, 0.0, 0.0, // �����_�̍��W
			0.0, 1.0, 0.0); // ��ʂ̏�������w���x�N�g��

		glRotatef(angle[0], 1.0, 0.0, 0.0);
		glRotatef(angle[1], 0.0, 1.0, 0.0);
		glRotatef(angle[2], 0.0, 0.0, 1.0);

		glScaled(scale_facter, scale_facter, scale_facter);
		glTranslated(0, 0, 0);

		static const GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };  /* �ގ� (�F) */

		/* �ގ��̐ݒ� */
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

		/* �A���t�@�e�X�g�J�n */
		glEnable(GL_ALPHA_TEST);

		/* �e�N�X�`���}�b�s���O�J�n */
		glEnable(GL_TEXTURE_2D);

		/* ����`�� */
		gluQuadricTexture(Sphere, 1);
		gluSphere(Sphere, 1.0, 36, 18);

		/* �e�N�X�`���}�b�s���O�I�� */
		glDisable(GL_TEXTURE_2D);

		//���W�n
		//(-,0,0) ���k��0�A���o90	
		//(0,-,0) ���k��0�A���o0
		//(+,0,0) ���k��0�A���o90
		//(0,+,0) ���k��0�A���o180
		//(0,0,+) �����90�A���o0
		//(0,0,-) ���k��90�A���o0
		/*
		(X)  = (0 -1)(x)
		(Y)	(1  0)(y)
		*/

		glPushMatrix();
		glTranslated(1, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		gluSphere(Sattelite, 0.1, 4, 2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, 1, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		gluSphere(Sattelite, 0.1, 4, 2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, 0, 1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
		gluSphere(Sattelite, 0.1, 4, 2);
		glPopMatrix();



		glPushMatrix();
		//printf("[trans] %f %f %f\n", trans[0], trans[1], trans[2]);
		glTranslated(trans[0, 0], trans[0, 1], trans[0, 2]);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);

		gluSphere(Sattelite, 0.04, 4, 2);
		glPopMatrix();

		for (int i = 1; i < 1800; i++){
			glPushMatrix();
			//printf("[trans] %f %f %f\n", trans[0], trans[1], trans[2]);
			glTranslated(trans[i,0], trans[i,1], trans[i,2]);

			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

			gluSphere(Sattelite, 0.02, 4, 2);
			glPopMatrix();
		}

		glEnd();



		/* �A���t�@�e�X�g�I�� */
		glDisable(GL_ALPHA_TEST);
	}
	GLAdapter->EndRender();
}

System::Void MainForm::myMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button != System::Windows::Forms::MouseButtons::Left&&e->Button != System::Windows::Forms::MouseButtons::Right){
		return;
	}

	Control^ control = dynamic_cast<Control^>(sender);

	startPoint = control->PointToScreen(System::Drawing::Point(e->X, e->Y));

	if (e->Button == System::Windows::Forms::MouseButtons::Left){
		control->MouseMove += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseMoveLeft);
		control->MouseUp += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseUpLeft);
	}
	else{
		control->MouseMove += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseMoveRight);
		control->MouseUp += gcnew MouseEventHandler(this, &sample10::MainForm::myMouseUpRight);
	}
}

System::Void MainForm::myMouseMoveRight(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Control^ control = dynamic_cast<Control^>(sender);

	System::Drawing::Point endPoint = control->PointToScreen(System::Drawing::Point(e->X, e->Y));

	//theta[0] = (double)(endPoint.Y - startPoint.Y) / 5.0;
	theta[2] = (double)(endPoint.X - startPoint.X) / 5.0;

	startPoint.X = endPoint.X;
	startPoint.Y = endPoint.Y;
	//angle[0] += theta[0];
	angle[2] += theta[2];

	printf("[angle] %f %f %f\n", angle[0], angle[1], angle[2]);
	panelRefresh();
}

System::Void MainForm::myMouseUpRight(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Control^ control = dynamic_cast<Control^>(sender);

	control->MouseMove -= gcnew MouseEventHandler(this, &sample10::MainForm::myMouseMoveRight);
	control->MouseUp -= gcnew MouseEventHandler(this, &sample10::MainForm::myMouseUpRight);

	panelRefresh();
}

System::Void MainForm::myMouseMoveLeft(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Control^ control = dynamic_cast<Control^>(sender);

	System::Drawing::Point endPoint = control->PointToScreen(System::Drawing::Point(e->X, e->Y));

	theta[0] = (double)(endPoint.Y - startPoint.Y) / 5.0;
	theta[1] = (double)(endPoint.X - startPoint.X) / 5.0;

	startPoint.X = endPoint.X;
	startPoint.Y = endPoint.Y;
	angle[0] += theta[0];
	angle[2] += theta[1];

	printf("[angle] %f %f %f\n", angle[0], angle[1], angle[2]);
	panelRefresh();
}

System::Void MainForm::myMouseUpLeft(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Control^ control = dynamic_cast<Control^>(sender);

	control->MouseMove -= gcnew MouseEventHandler(this, &sample10::MainForm::myMouseMoveLeft);
	control->MouseUp -= gcnew MouseEventHandler(this, &sample10::MainForm::myMouseUpLeft);

	panelRefresh();
}

System::Void MainForm::myMouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	float rotateDirection = e->Delta * SystemInformation::MouseWheelScrollLines / 120.;
	printf("[mouce wheel] %f\n", rotateDirection);

	if (rotateDirection > 0){
		scale_facter += 0.1;
	}
	else{
		scale_facter -= 0.1;
	}

	printf("[mouce wheel scale] %f\n", scale_facter);

	panelRefresh();
}

GLuint MainForm::readTexture()
{
	int width, height;

	cv::Mat img = cv::imread(texture1);
	cvtColor(img, img, CV_BGR2RGB);
	width = img.cols;
	height = img.rows;

	cv::Mat img_tmp;
	cv::flip(img, img_tmp, 0);

	cv::Mat roi1 = cv::Mat(img, cv::Rect(0, 0, img.cols / 4, img.rows));
	cv::Mat roi2 = cv::Mat(img, cv::Rect(img.cols / 4, 0, 3*img.cols / 4, img.rows));
	cv::Mat roi1_tmp = cv::Mat(img_tmp, cv::Rect(0, 0, 3*img.cols / 4, img.rows));
	cv::Mat roi2_tmp = cv::Mat(img_tmp, cv::Rect(3*img.cols / 4, 0, img.cols / 4, img.rows));

	/*cv::Mat roi1 = cv::Mat(img, cv::Rect(0, 0, img.cols / 2, img.rows));
	cv::Mat roi2 = cv::Mat(img, cv::Rect(img.cols / 2, 0, img.cols / 2, img.rows));
	cv::Mat roi1_tmp = cv::Mat(img_tmp, cv::Rect(0, 0, img.cols / 2, img.rows));
	cv::Mat roi2_tmp = cv::Mat(img_tmp, cv::Rect(img.cols / 2, 0, img.cols / 2, img.rows));*/

	roi2_tmp.copyTo(roi1);
	roi1_tmp.copyTo(roi2);

	//Bitmap^ bmp=mat2bmp(img);

	imwrite("tex.png", img);

	GLAdapter->BeginRender();
	{
		glGenTextures(1, &tex);

		glBindTexture(GL_TEXTURE_2D, tex);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, img.ptr());

		/* �e�N�X�`�����g��E�k��������@�̎w�� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		/* �e�N�X�`���� */
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


		/* �A���t�@�e�X�g�̔��ʊ֐� */
		glAlphaFunc(GL_GREATER, 0.5);

		/* �����ݒ� */
		glClearColor(0.3, 0.3, 1.0, 0.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		/* �����̏����ݒ� */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);

		Sphere = gluNewQuadric();
		Sattelite = gluNewQuadric();
		//gluQuadricDrawStyle(Sphere, GLU_LINE);
	}
	GLAdapter->EndRender();

	return tex;
}

System::Void MainForm::drawAntenna(double lx, double ly, int nx, int ny, double px, double py, Color color,PictureBox^ pictureBox)
{
	int w = pictureBox->Width;
	int h = pictureBox->Height;

	//Bitmap�N���X�̍쐬
	//Bitmap^ bmp = gcnew Bitmap(w, h);
	//pictureBox->Image = bmp;

	//�g��`��
	Graphics^ g = Graphics::FromImage(pictureBox->Image);

	//�s�N�`���{�b�N�X�̔w�i�F�ŃN���A����B
	//g->Clear(pictureBox->BackColor);

	Pen^ p = gcnew Pen(color, 2);
	System::Drawing::Rectangle rect;

	int scale = 20;

	for (int i = 0; i < nx; i++){
		for (int j = 0; j < ny; j++){
			rect = System::Drawing::Rectangle(px*scale+w/2+(i*lx-nx*lx/2)*scale, py*scale+h/2+(j*ly-ny*ly/2)*scale, lx*scale, ly*scale);
			g->DrawRectangle(p, rect);
			//printf("[Draw antenna] %d %d\n", i, j);
		}
	}
	
	pictureBox->Refresh();
	p->~Pen();
	g->~Graphics();
}
