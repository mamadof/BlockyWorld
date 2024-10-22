#include "gui.hpp"
#include "imgui/imgui.h"
#include "share.hpp"
#include "gameWorld.hpp"

static ImVec2 PlayerInvSize(900,900);
static ImVec2 PlayerInvPos((float)sf_window.getSize().x/2,(float)sf_window.getSize().y/2);
static ImVec2 PlayerInvContainerSize(50,50);

static ImVec2 windowPadding(9,9);
static ImVec2 framePadding(0,0);
static ImVec2 itemSpacing(5,5);


static ImVec4 color;

void GGUI::handleGui()
{
    if (pworld->player()->m_isInventoryOpen)
    {
        openPlayerInventory();
    }
}

static void openPlayerInventory()
{
    // ImGui::ShowDemoWindow();
    // ImGui::Begin("Inventory", &pworld->player()->m_isInventoryOpen,
    // ImGuiWindowFlags_NoCollapse|
    // ImGuiWindowFlags_NoResize|
    // ImGuiWindowFlags_NoMove|
    // ImGuiWindowFlags_AlwaysAutoResize);

    // pworld->player()->m_inventoryPos = 
    // sf::Vector2f(
    // ((float)sf_window.getSize().x/2) - ImGui::GetWindowWidth()/2,
    // ((float)sf_window.getSize().y/2) - ImGui::GetWindowHeight()/2);

    // ImGui::SetWindowPos(ImVec2(pworld->player()->m_inventoryPos));

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, windowPadding);
    // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, framePadding);
    // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, itemSpacing);
    
    // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255,255,255,0.5));
    // ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255,255,255,0.6));
    // ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255,255,255,0.7));

    
    // for (int y = 0; y < 4; y++)
    // {
    //     for (int x = 0; x < 9; x++)
    //     {
    //         ImGui::SameLine();
    //         ImGui::Button("##",PlayerInvContainerSize);
    //         if (ImGui::IsItemClicked())printf("clicked biatch %d\n", x);
    //     }
    //     //for left hand 
    //     if (y == 3)
    //     {
    //         ImGui::SameLine(60*9);
    //         ImGui::Button("##",PlayerInvContainerSize);
    //     }
    //     ImGui::NewLine();
    //     if (y == 2)
    //     {
    //         ImGui::NewLine();
    //         ImGui::NewLine();
    //     }
    // }
    // ImGui::PopStyleVar(3);
    // ImGui::PopStyleColor(3);
    // ImGui::End();
}