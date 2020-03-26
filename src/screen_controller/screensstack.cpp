#include "screensstack.h"

ScreensStack::ScreensStack(QWidget* parent) : QWidget(parent), m_layout(this)
{
  setLayout(&m_layout);
  m_layout.setMargin(0);
}

void ScreensStack::push(QWidget* widget)
{
  if (false == m_widgets.empty())
  {
    QWidget* top = m_widgets.front();
    top->hide();
  }
  m_layout.addWidget(widget);
  m_widgets.push_front(widget);
  widget->show();
}

bool ScreensStack::check_empty()
{
  if (false == m_widgets.empty())
    return false;

  emit back();
  return true;
}

void ScreensStack::pop()
{
  if (check_empty())
    return;

  m_widgets.front()->hide();
  m_widgets.pop_front();

  if (check_empty())
    return;

  m_widgets.front()->show();
}

int ScreensStack::lenght()
{
  return m_widgets.length();
}
