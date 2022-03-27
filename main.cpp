#include <graphics.h>
#include <math.h>

struct CzfLine {
	int x1;
	int y1;
	int x2;
	int y2;
};

CzfLine line1;

//mouse status
bool isMouseMoving = false;
int xMouse, yMouse;
int xLast, yLast;
int xFirst, yFirst;

//redraw
bool isRedraw = false;

void calcVertexes(double start_x, double start_y, double end_x, double end_y, double& x1, double& y1, double& x2, double& y2) {
	double arrow_lenght_ = 20.0;
	double arrow_degrees_ = 25 * M_PI / 180;

	double angle = atan2 (end_y - start_y, end_x - start_x) + M_PI;

	x1 = end_x + arrow_lenght_ * cos(angle - arrow_degrees_);
	y1 = end_y + arrow_lenght_ * sin(angle - arrow_degrees_);
	x2 = end_x + arrow_lenght_ * cos(angle + arrow_degrees_);
	y2 = end_y + arrow_lenght_ * sin(angle + arrow_degrees_);
}

void setup() {
	initgraph(640, 480, INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcolor(BLACK);
	setfont(20, 0, "����");
	setbkmode(TRANSPARENT);
	//���������
//	ege_enable_aa(true);
	//xor��ʽդ��ͼ
	setwritemode(R2_XORPEN);


}

void show() {
	if (isRedraw) {
		cleardevice();
		setlinestyle(SOLID_LINE, 0, 2);
		line(line1.x1, line1.y1, line1.x2, line1.y2);

		double x1, y1, x2, y2;
		calcVertexes(line1.x1, line1.y1, line1.x2, line1.y2, x1, y1, x2, y2);
		line(line1.x2, line1.y2, x1, y1);
		line(line1.x2, line1.y2, x2, y2);

		calcVertexes(line1.x2, line1.y2, line1.x1, line1.y1, x1, y1, x2, y2);
		line(line1.x1, line1.y1, x1, y1);
		line(line1.x1, line1.y1, x2, y2);


		isRedraw = false;
	}
}
void update() {
	while (mousemsg()) {
		mouse_msg msg = getmouse();
		//���������λ�ü�¼
		if (msg.is_move() && isMouseMoving ) {
			//���ݻ���͵�ǰλ���ƶ�����
			setcolor(YELLOW);
			setlinestyle(DOTTED_LINE, 0, 3);

			line(xFirst, yFirst, xLast, yLast);

			double x1, y1, x2, y2;
			calcVertexes(xFirst, yFirst, xLast, yLast, x1, y1, x2, y2);
			line(xLast, yLast, x1, y1);
			line(xLast, yLast, x2, y2);

			line(xFirst, yFirst, msg.x, msg.y);

			calcVertexes(xFirst, yFirst, msg.x, msg.y, x1, y1, x2, y2);
			line(msg.x, msg.y, x1, y1);
			line(msg.x, msg.y, x2, y2);
			//�����󣬸ı����
			xLast = msg.x;
			yLast = msg.y;


		} else if (msg.is_left()) {
			if (msg.is_down()) {
				//���û���Ϊ���λ��
				xFirst = msg.x;
				yFirst = msg.y;
				xMouse = msg.x;
				yMouse = msg.y;
				xLast = msg.x;
				yLast = msg.y;

				setcolor(YELLOW);
				setlinestyle(DOTTED_LINE, 0, 3);
				double x1, y1, x2, y2;
				calcVertexes(xFirst, yFirst, xLast, yLast, x1, y1, x2, y2);
				line(xLast, yLast, x1, y1);
				line(xLast, yLast, x2, y2);

				isMouseMoving = true;
			} else {
				isMouseMoving = false;
				line1.x1 = xFirst;
				line1.y1 = yFirst;
				line1.x2 = msg.x;
				line1.y2 = msg.y;
				isRedraw = true;
			}
		}
	}
}
int main() {
	setup();
	for (; is_run(); delay_fps(60)) {
		show();
		update();
	}

	closegraph();

	return 0;
}
