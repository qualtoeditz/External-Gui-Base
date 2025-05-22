#include "Drawing.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <chrono>

LPCSTR Drawing::lpWindowName = "EXT3RNAL BLACK V1";
ImVec2 Drawing::vWindowSize = { 460, 350 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
    bDraw = true;
}

bool Drawing::isActive()
{
    return bDraw == true;
}

bool CheckboxWithSound(const char* label, bool* v)
{
    bool changed = ImGui::Checkbox(label, v);
    if (changed && *v)
    {
        PlaySound(TEXT("C:\\Windows\\Media\\chimes.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    return changed;
}

void DrawGlow(ImDrawList* drawList, const ImVec2& pos, const ImVec2& size, ImU32 color, int layers = 6, float thickness = 1.5f)
{
    for (int i = 0; i < layers; i++)
    {
        float alpha = (1.0f - (float)i / (float)layers) * 0.15f;
        ImU32 col = (color & 0x00FFFFFF) | ((ImU32)(alpha * 255.0f) << 24);
        ImVec2 topLeft(pos.x - i, pos.y - i);
        ImVec2 bottomRight(pos.x + size.x + i, pos.y + size.y + i);
        drawList->AddRect(topLeft, bottomRight, col, 4.0f, 0, thickness);
    }
}

void Drawing::Draw()
{
    static bool bhopEnabled = false;
    static int delay = 100;
    static DWORD lastPressTime = 0;
    static int currentTab = 0;

    static bool aimbotEnabled = false;
    static float aimFov = 5.0f;
    static int aimBone = 0;

    static bool autoStrafe = false;
    static bool edgeJump = false;

    static bool nightMode = false;
    static bool thirdPerson = false;
    static int thirdPersonKey = 0;

    static ImVec4 guiColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    static bool glowEffect = false;

    if (!Drawing::isActive())
        return;

    ImGui::SetNextWindowSize(Drawing::vWindowSize, ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(guiColor.w);

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);

    if (glowEffect)
    {
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        ImVec2 size = Drawing::vWindowSize;
        ImU32 glowColor = ImGui::ColorConvertFloat4ToU32(ImVec4(guiColor.x, guiColor.y, guiColor.z, 1.0f));
        DrawGlow(drawList, ImVec2(100, 100), size, glowColor, 6, 2.5f);
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, guiColor);
    ImGui::PushStyleColor(ImGuiCol_Border, guiColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, glowEffect ? 2.0f : 1.0f);

    ImGui::Begin(Drawing::lpWindowName, &Drawing::bDraw, Drawing::WindowFlags);
    {
        if (ImGui::Button("Aim")) currentTab = 1;
        ImGui::SameLine();
        if (ImGui::Button("Movement")) currentTab = 2;
        ImGui::SameLine();
        if (ImGui::Button("Misc")) currentTab = 3;
        ImGui::SameLine();
        if (ImGui::Button("Settings")) currentTab = 4;
        ImGui::SameLine();
        if (ImGui::Button("Info")) currentTab = 5;

        ImGui::Separator();

        if (currentTab == 0)
        {
            ImGui::Text("Welcome to EXT3RNAL BLACK V1");
            CheckboxWithSound("Enable Bhop", &bhopEnabled);
            ImGui::SliderInt("Delay (ms)", &delay, 10, 500);
        }
        else if (currentTab == 1)
        {
            CheckboxWithSound("Enable Aimbot", &aimbotEnabled);
            ImGui::SliderFloat("Aimbot FOV", &aimFov, 1.0f, 30.0f);
            const char* bones[] = { "Head", "Neck", "Chest", "Stomach" };
            ImGui::Combo("Target Bone", &aimBone, bones, IM_ARRAYSIZE(bones));
        }
        else if (currentTab == 2)
        {
            CheckboxWithSound("Bunnyhop", &bhopEnabled);
            ImGui::SliderInt("Hop Delay", &delay, 10, 500);
            CheckboxWithSound("Auto Strafe", &autoStrafe);
            CheckboxWithSound("Edge Jump", &edgeJump);
        }
        else if (currentTab == 3)
        {
            CheckboxWithSound("Night Mode", &nightMode);
            CheckboxWithSound("Third Person", &thirdPerson);
            ImGui::InputInt("Third Person Key", &thirdPersonKey);
        }
        else if (currentTab == 4)
        {
            ImGui::Text("GUI Settings");
            ImGui::ColorEdit4("GUI Color", (float*)&guiColor, ImGuiColorEditFlags_NoInputs);
            CheckboxWithSound("Enable Glow Border", &glowEffect);
        }
        else if (currentTab == 5)
        {
            ImGui::Text("EXT3RNAL BLACK V1");
            ImGui::Text("Created with ❤️ by you");
            ImGui::Text("Press INSERT to toggle GUI");
        }

        if (bhopEnabled && (GetAsyncKeyState(VK_SPACE) & 0x8000))
        {
            DWORD now = GetTickCount();
            if (now - lastPressTime >= (DWORD)delay)
            {
                INPUT inputs[2] = {};
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_SPACE;
                inputs[0].ki.dwFlags = 0;

                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = VK_SPACE;
                inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

                SendInput(2, inputs, sizeof(INPUT));
                lastPressTime = now;
            }
        }
    }
    ImGui::End();

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar();
}
