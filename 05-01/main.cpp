#include <Novice.h>
#include <KamataEngine.h>
#include "GameManager.h"

using namespace KamataEngine;

constexpr char kWindowTitle[] = "LE2A_リ_ショウコウ";
constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameManager game(kWindowTitle,kWindowWidth,kWindowHeight);

	return game.Run();
}
