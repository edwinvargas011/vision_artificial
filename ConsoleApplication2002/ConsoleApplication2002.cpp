#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include<opencv2/opencv.hpp>


using namespace cv;
using namespace std;
int parametro1 = 30;
int parametro2 = 100;
int menu();
void mostrarFoto(VideoCapture c);
void mostrarVideo(VideoCapture c, int filtro);
int main() {
	VideoCapture c;
	int op;
	do
	{
		op = menu();
		switch (op) {
		case 0: cout << " Bye" << endl;
			break;
		case 1: mostrarFoto(c);
			break;
		case 2: mostrarVideo(c, 0);
			break;
		case 3: mostrarVideo(c, 1);
			break;
		case 4: mostrarVideo(c, 2);
			break;
		}
	} while (op != 0);
	return 1;
}
int menu() {
	int opcion;
	cout << "...... MENU ......" << endl;
	cout << "0. Salir" << endl;
	cout << "1. Foto" << endl;
	cout << "2. Video" << endl;
	cout << "3. Deteccion de Bordes" << endl;
	cout << "4. Distorcion" << endl;
	cout << "Selecciona una Opcion: ";
	cin >> opcion;
	return opcion;
}
void mostrarFoto(VideoCapture c) {
	c.open(0);
	if (!c.isOpened()) {
		cout << "Error al tratar de inicializar la camara" << endl;
	}
	else {
		namedWindow("Foto", 1);
		moveWindow("Foto", 50, 200);
		Mat frame;
		c >> frame;
		flip(frame, frame, 1);
		imshow("Foto", frame);
		waitKey(0);
		destroyWindow("Foto");
	}
	c.release();
}
void mostrarVideo(VideoCapture c, int filtro) {
	c.open(0);
	if (!c.isOpened()) {
		cout << "Error al tratar de inicializar la camara" << endl;
	}
	else {
		namedWindow("Video Original", 1);
		moveWindow("Video Original", 50, 200);
		if (filtro != 0) {
			namedWindow("Video Filtrado", 1);
			moveWindow("Video Filtrado", 700, 200);
			createTrackbar("tb1", "Video Original", &parametro1, 500);
			createTrackbar("tb2", "Video Original", &parametro2, 500);
		}
		while (true) {
			Mat frame;
			Mat filtrada;
			c >> frame;
			flip(frame, frame, 1);
			imshow("Video Original", frame);
			switch (filtro) {
			case 1:
				Canny(frame, filtrada, parametro1, parametro2);
				imshow("Video Filtrado", filtrada);
				break;
			case 2:
				parametro1 = (parametro1 > 0) ? parametro1 : 1;
				blur(frame, filtrada, Size(parametro1, parametro1));
				imshow("Video Filtrado", filtrada);
				break;
			}
			if (waitKey(30) >= 0) {
				break;
			}
		}
		destroyAllWindows();
	}
	c.release();
}
