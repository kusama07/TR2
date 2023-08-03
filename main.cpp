#include <Novice.h>
#include "Blend.h"
#include "Vector4.h"
#include <iostream>
#include <algorithm>
#include "ImGuiManager.h"
#include "Vector2.h"

const char kWindowTitle[] = "LE2B_10_クサマリョウト";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

struct Back {
	Vector4i pos;
};

struct VanishingPoint {
	Vector2 pos;
	unsigned int color;
};

struct Segment {
	Vector2 start;
	Vector2 end;
	unsigned int color; // 色
};

// 2点間の交点を計算する関数
Vector2 calculateIntersection(const Segment& s1, const Segment& s2) {
    Vector2 intersect;

    float denominator = (s1.end.x - s1.start.x) * (s2.end.y - s2.start.y) - (s1.end.y - s1.start.y) * (s2.end.x - s2.start.x);
    if (denominator == 0) {
        // 2線分が平行で交点が存在しない場合は、原点を返す
        intersect.x = 0.0f;
        intersect.y = 0.0f;
    } else {
        float t = ((s2.start.x - s1.start.x) * (s2.end.y - s2.start.y) - (s2.start.y - s1.start.y) * (s2.end.x - s2.start.x)) / denominator;
        intersect.x = s1.start.x + t * (s1.end.x - s1.start.x);
        intersect.y = s1.start.y + t * (s1.end.y - s1.start.y);
    }

    return intersect;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	VanishingPoint vanisingPosint1 = {
		{100.0f, 400.0f},
		BLUE,
	};

	VanishingPoint vanisingPosint2 = {
		{1100.0f, 400.0f},
		BLUE,
	};

	Segment segment1 = {
	  {100.0f,  400.0f},
	  {1000.0f, 400.0f},
	  WHITE
	};

	Segment segment2 = {
	  {100.0f, 400.0f},
	  {1000.0f, 400.0f},
	  WHITE
	};


	Segment segment3 = {
	  {1100.0f, 400.0f},
	  {100.0f, 400.0f},
	  WHITE
	};

	Segment segment4 = {
	  {1100.0f, 400.0f},
	  {100.0f, 400.0f},
	  WHITE
	};

	Segment segment5 = {
	  {300.0f, 200.0f},
	  {300.0f, 600.0f},
	  BLUE
	};

	Segment segment6 = {
	  {900.0f, 200.0f},
	  {900.0f, 600.0f},
	  BLUE
	};

	const int backNum = 20;

	Back back[backNum];

	for (int i = 0; i < backNum; i++) {
		back[i].pos.x = 0;
		back[i].pos.y = 0;
		back[i].pos.h = kWindowHeight;
		back[i].pos.w = kWindowWidth;
	}

	int backGH = Novice::LoadTexture("./Resources/back.png");
	int back1GH = Novice::LoadTexture("./Resources/back1.png");

	int twoPointGH = Novice::LoadTexture("./Resources/twoPointBack.png");
	int twoPoint1GH = Novice::LoadTexture("./Resources/twoPointBack1.png");

	int red = 255;
	int blue = 255;
	int green = 255;
	int alpha = 50;

	static bool OnePointPerspectiveFlag = false;
	static bool TwoPointPerspectiveFlag = false;

	static bool DrawLineFlag = false;

	static int mode = 0;

	enum {
		MODE_1,
		MODE_2,
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector2 intersect = (calculateIntersection(segment1, segment3));
		Vector2 intersect1 = (calculateIntersection(segment2, segment4));
		Vector2 intersect2 = (calculateIntersection(segment5, segment1));
		Vector2 intersect3 = (calculateIntersection(segment5, segment2));
		Vector2 intersect4 = (calculateIntersection(segment6, segment3));
		Vector2 intersect5 = (calculateIntersection(segment6, segment4));


		ImGui::Begin("Perspective");

		if (ImGui::TreeNode("OnePointPerspective")) {
			ImGui::Checkbox("isEnable", &OnePointPerspectiveFlag);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("TwoPointPerspective")) {
			ImGui::Checkbox("isEnable", &TwoPointPerspectiveFlag);
			ImGui::Checkbox("DrawLineFlag", &DrawLineFlag);
			ImGui::RadioButton("mode 1", &mode, MODE_1); ImGui::SameLine(); ImGui::RadioButton("mode 2", &mode, MODE_2);
			if (mode == MODE_1) {
				if (keys[DIK_Q] && preKeys[DIK_Q]) {
					segment1.end.y -= 3;
					segment2.end.y += 3;
				}
				if (keys[DIK_E] && preKeys[DIK_E]) {
					segment1.end.y += 3;
					segment2.end.y -= 3;
				}

			}
			else if (mode == MODE_2) {
				if (keys[DIK_Q] && preKeys[DIK_Q]) {
					segment3.end.y -= 3;
					segment4.end.y += 3;
				}
				if (keys[DIK_E] && preKeys[DIK_E]) {
					segment3.end.y += 3;
					segment4.end.y -= 3;
				}
			}



			ImGui::TreePop();
		}

		ImGui::End();

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///

			if (OnePointPerspectiveFlag) {
				Novice::DrawSprite(0, 0, back1GH, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

				for (int i = 0; i < backNum; i++) {

					// iを0～1の範囲に変換
					float t = static_cast<float>(i) / (backNum - 1);

					// スケールを調整（0.2から1.0の範囲で増加させる）
					float scaleX = 0.2f + t * 0.8f;
					float scaleY = 0.2f + t * 0.8f;

					int centerX = static_cast<int>((kWindowWidth - back[i].pos.w * scaleX) / 2);
					int centerY = static_cast<int>((kWindowHeight - back[i].pos.h * scaleY) / 2);

					// 画像を描画
					Novice::DrawSpriteRect(centerX, centerY, 0, 0,
						back[i].pos.h, back[i].pos.w, backGH, scaleX, scaleY, 0.0f, GetColor(red, blue, green, alpha));
				}
			}

			if (TwoPointPerspectiveFlag) {

				Novice::DrawQuad(
					static_cast<int>(intersect2.x), static_cast<int>(intersect2.y), 
					static_cast<int>(intersect.x),  static_cast<int>(intersect.y) ,
					static_cast<int>(intersect3.x), static_cast<int>(intersect3.y),
					static_cast<int>(intersect1.x), static_cast<int>(intersect1.y),
					0,0,
					1280, 720,
					twoPointGH, GetColor(red, blue, green, 255));

				Novice::DrawQuad(
					static_cast<int>(intersect.x), static_cast<int>(intersect.y),
					static_cast<int>(intersect4.x), static_cast<int>(intersect4.y),
					static_cast<int>(intersect1.x), static_cast<int>(intersect1.y),
					static_cast<int>(intersect5.x), static_cast<int>(intersect5.y),
					0, 0,
					1280, 720,
					twoPoint1GH, GetColor(red, blue, green, 255));

				if (DrawLineFlag) {
					//消失点
					Novice::DrawEllipse(static_cast<int>(vanisingPosint1.pos.x), static_cast<int>(vanisingPosint1.pos.y), 10, 10, 0.0f, vanisingPosint1.color, kFillModeSolid);
					Novice::DrawEllipse(static_cast<int>(vanisingPosint2.pos.x), static_cast<int>(vanisingPosint2.pos.y), 10, 10, 0.0f, vanisingPosint2.color, kFillModeSolid);

					Novice::DrawLine(static_cast<int>(vanisingPosint1.pos.x), static_cast<int>(vanisingPosint1.pos.y), static_cast<int>(segment1.end.x), static_cast<int>(segment1.end.y), segment1.color);
					Novice::DrawLine(static_cast<int>(vanisingPosint1.pos.x), static_cast<int>(vanisingPosint1.pos.y), static_cast<int>(segment2.end.x), static_cast<int>(segment2.end.y), segment2.color);

					Novice::DrawLine(static_cast<int>(vanisingPosint2.pos.x), static_cast<int>(vanisingPosint2.pos.y), static_cast<int>(segment3.end.x), static_cast<int>(segment3.end.y), segment3.color);
					Novice::DrawLine(static_cast<int>(vanisingPosint2.pos.x), static_cast<int>(vanisingPosint2.pos.y), static_cast<int>(segment4.end.x), static_cast<int>(segment4.end.y), segment4.color);

					//交点
					Novice::DrawEllipse(static_cast<int>(intersect.x), static_cast<int>(intersect.y), 10, 10, 0.0f, WHITE, kFillModeSolid);
					Novice::DrawEllipse(static_cast<int>(intersect1.x), static_cast<int>(intersect1.y), 10, 10, 0.0f, WHITE, kFillModeSolid);

					//縦線
					Novice::DrawLine(static_cast<int>(segment5.start.x), static_cast<int>(segment5.start.y), static_cast<int>(segment5.end.x), static_cast<int>(segment5.end.y), segment5.color);
					Novice::DrawLine(static_cast<int>(segment6.start.x), static_cast<int>(segment6.start.y), static_cast<int>(segment6.end.x), static_cast<int>(segment6.end.y), segment5.color);

					Novice::DrawEllipse(static_cast<int>(intersect2.x), static_cast<int>(intersect2.y), 10, 10, 0.0f, WHITE, kFillModeSolid);
					Novice::DrawEllipse(static_cast<int>(intersect3.x), static_cast<int>(intersect3.y), 10, 10, 0.0f, WHITE, kFillModeSolid);

					Novice::DrawEllipse(static_cast<int>(intersect4.x), static_cast<int>(intersect4.y), 10, 10, 0.0f, WHITE, kFillModeSolid);
					Novice::DrawEllipse(static_cast<int>(intersect5.x), static_cast<int>(intersect5.y), 10, 10, 0.0f, WHITE, kFillModeSolid);
				}

			}

			///
			/// ↑描画処理ここまで
			///

			// フレームの終了
			Novice::EndFrame();

			// ESCキーが押されたらループを抜ける
			if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
				break;
			}
		}

		// ライブラリの終了
		Novice::Finalize();
		return 0;
	}
