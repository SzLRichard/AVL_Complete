#include <iostream>
#include "AVL.h"
#include "node.h"
#include <windows.h>
#include <string>
using namespace std;
bool better(const string& word, string& best, string current) {
    int n = word.length();
    int b = best.length();
    int c = current.length();
    if (current.substr(0, n) == word && (c < b || best.substr(0, n) != word))
        return true;
    else return false;
    for (int i = 0;i < n;i++) {
        if ((c > i && current[i] == word[i]) && (b > i && best[i] != word[i]))
            return true;
    }
    return false;
}
string findClosest(node<string>* root, const string& word, string& closest) {
    if (root == nullptr)
        return closest;
    if (root->getValue() == word)
        return root->getValue();
    if (closest.empty() || better(word, closest, root->getValue()))
        closest = root->getValue();
    if (word < root->getValue())
        return findClosest(root->getLeft(), word, closest);
    else
        return findClosest(root->getRight(), word, closest);
}
HHOOK hHook = NULL;
std::string buffer = "";
string replacement;
AVL<string> tree;
bool running = true;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        int key = pKeyboard->vkCode;
        if (key) {
            if (key == VK_ESCAPE) {
                running = false;
                return CallNextHookEx(hHook, nCode, wParam, lParam);
            }
            if (key == 8 && !empty(buffer)) {
                buffer.erase(buffer.size() - 1);
                replacement.clear();
            }
            else
                if (key == 32 || key == 188 || key == 190 || key == 13) {
                    if (!empty(buffer)) {
                        tree.insert(buffer);
                    }
                    buffer.clear();
                    replacement.clear();
                }
                else if (key == 192) {
                    if (empty(buffer)) {
                        if (!empty(replacement)) {
                            string temp = replacement;
                            node<string>* prev = tree.previous(replacement);
                            if (prev == nullptr)
                                return 192;
                            int n = replacement.size();
                            for (int i = 0; i < n; ++i) {
                                INPUT input;
                                input.type = INPUT_KEYBOARD;
                                input.ki.wVk = VK_BACK;
                                input.ki.dwFlags = 0;
                                SendInput(1, &input, sizeof(INPUT));
                                Sleep(1);
                            }
                            replacement = prev->getValue();
                            temp = replacement;
                            for (char c : replacement) {
                                INPUT input;
                                input.type = INPUT_KEYBOARD;
                                input.ki.wVk = 0;
                                input.ki.wScan = tolower(c);
                                input.ki.dwFlags = KEYEVENTF_UNICODE;
                                SendInput(1, &input, sizeof(INPUT));
                            }
                            buffer.clear();
                            replacement = temp;
                            return 192;
                        }
                        else {
                            buffer.clear();
                            replacement.clear();
                            return 192;
                        }

                    }

                }
                else if (key == 220) {
                    if (empty(buffer)) {
                        if (!empty(replacement)) {
                            string temp = replacement;
                            int n = replacement.size();
                            for (int i = 0; i < n; ++i) {
                                INPUT input;
                                input.type = INPUT_KEYBOARD;
                                input.ki.wVk = VK_BACK;
                                input.ki.dwFlags = 0;
                                SendInput(1, &input, sizeof(INPUT));
                                Sleep(1);
                            }
                            tree.remove(temp);
                            buffer.clear();
                            replacement.clear();
                            return 220;
                        }
                        else {
                            buffer.clear();
                            replacement.clear();
                            return 220;
                        }

                    }

                }
                else if (key == 9) {
                    string temp;
                    if (empty(buffer)) {
                        if (!empty(replacement)) {
                            temp = replacement;
                            node<string>* next = tree.next(replacement);
                            if (next == nullptr) {
                                return 9;
                            }
                            int n = replacement.size();
                            for (int i = 0; i < n; ++i) {
                                INPUT input;
                                input.type = INPUT_KEYBOARD;
                                input.ki.wVk = VK_BACK;
                                input.ki.dwFlags = 0;
                                SendInput(1, &input, sizeof(INPUT));
                                Sleep(1);
                            }
                            replacement = next->getValue();
                            temp = replacement;
                            for (char c : replacement) {
                                INPUT input;
                                input.type = INPUT_KEYBOARD;
                                input.ki.wVk = 0;
                                input.ki.wScan = tolower(c);
                                input.ki.dwFlags = KEYEVENTF_UNICODE;
                                SendInput(1, &input, sizeof(INPUT));
                            }
                            buffer.clear();
                            replacement = temp;
                            return 9;
                        }
                        else {
                            buffer.clear();
                            return 9;
                        }
                    }
                    int n = buffer.size();
                    string target = buffer;
                    for (int i = 0; i < n; ++i) {
                        INPUT input;
                        input.type = INPUT_KEYBOARD;
                        input.ki.wVk = VK_BACK;
                        input.ki.dwFlags = 0;
                        SendInput(1, &input, sizeof(INPUT));
                        Sleep(1);
                    }
                    string closest = "";
                    replacement = findClosest(tree.getRoot(), target, closest);
                    temp = replacement;
                    for (char c : replacement) {
                        INPUT input;
                        input.type = INPUT_KEYBOARD;
                        input.ki.wVk = 0;
                        input.ki.wScan = tolower(c);
                        input.ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input, sizeof(INPUT));
                    }
                    buffer.clear();
                    replacement = temp;
                    return 9;
                }
                else {
                    if ((char)key) {
                        buffer += (char)key;
                    }
                    replacement.clear();
                }
        }
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void SetHook() {
    if (!(hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0))) {
        MessageBox(NULL, L"Failed to install hook!", L"Error", MB_ICONERROR);
    }
}

void ReleaseHook() {
    if (hHook) {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
    }
}

int main() {
    AllocConsole();
    FILE* a, * b;
    freopen_s(&a, "CONOUT$", "w", stdout);
    freopen_s(&b, "CONIN$", "r", stdin);
    SetHook();
    cout << "Autocomplete is active. Press (esc) to quit." << endl;
    MSG msg;

    while (running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) {
                running = false;
                break;
            }
            Sleep(1);
        }
    }

    ReleaseHook();
    cout << "Program finished." << endl << "List of elements in the tree:" << endl;
    tree.print();
    fclose(stdout);
    fclose(stdin);
    FreeConsole();

    return 0;
}
