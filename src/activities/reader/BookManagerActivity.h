#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <memory>

#include "../Activity.h"

class BookManagerActivity final : public Activity {
  TaskHandle_t displayTaskHandle = nullptr;
  SemaphoreHandle_t renderingMutex = nullptr;
  uint32_t currentPage = 0;
  int selectorIndex = 0;
  bool updateRequired = false;
  const std::function<void()> onGoBack;
  const std::function<void()> onSelectBook;
  const std::string bookPath;

  int getPageItems() const;

  static void taskTrampoline(void* param);
  [[noreturn]] void displayTaskLoop();
  void renderScreen();

 public:
  explicit BookManagerActivity(GfxRenderer& renderer, MappedInputManager& mappedInput,
                                             const std::function<void()>& onGoBack, const std::function<void()>& onSelectBook, const std::string& bookPath)
      : Activity("BookManagerActivity", renderer, mappedInput),
        onGoBack(onGoBack), onSelectBook(onSelectBook), bookPath(bookPath) {}
  void onEnter() override;
  void onExit() override;
  void loop() override;
};
