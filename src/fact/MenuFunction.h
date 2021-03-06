#pragma once

#include "Menu.h"
#include "menu_invoke.h"

namespace FactUtilEmbedded
{
  /*
  class MenuFunctionBase : public MenuCommand
  {
  };

  template <class TIn, class TOut>
  class MenuFunction : public MenuFunctionBase
  {
  protected:
    typedef TOut (*_handler)(TIn);

    const _handler handler;

  protected:
    virtual void handleCommand(Parameters p) override;

  public:
    MenuFunction(_handler handler) : handler(handler) {}
  };

  template <class TIn, class TOut>
  void MenuFunction<TIn, TOut>::handleCommand(IMenu::Parameters p)
  {
    TIn in1 = fromString<TIn>(p.parameters[0]);
    //TOut result =
    handler(in1);
  }
  */

  template <class _handler>
  class MenuFunction2 : public MenuCommand
  {
  protected:
    const _handler handler;

    virtual void handleCommand(Parameters p) override;

  public:
    MenuFunction2(_handler handler, PGM_P name, PGM_P desc) :
      MenuCommand(name, desc), handler(handler) {}

  #ifdef UNIT_TEST
    void _handleCommand(Parameters p)
    {
      handleCommand(p);
    }
  #endif
  };

  template <class TIn>
  class ActionFunc
  {
    typedef void (*action1)(TIn);
  };

/*
  template <class TIn>
  class MFWrapper : MenuFunction2<ActionFunc<TIn>::action1>
  {
  public:
    MFWrapper(_handler handler) :
      MenuFunction2<ActionFunc<TIn>::action1>(handler) {}
  }; */

  template <class _handler>
  void MenuFunction2<_handler>::handleCommand(IMenu::Parameters p)
  {
    uint8_t expectedParameterCount = invokeParamCount(handler);

    if(expectedParameterCount != p.count)
    {
      renderParameterError(expectedParameterCount, p.count);
      return;
    }

    validateInvokeNative(handler, p); // this *only* validates
    invoke(handler, p);
  }

  template <class THandler>
  inline MenuFunction2<THandler> createMenuFunction(THandler handler, PGM_P name = NULL, PGM_P desc = NULL)
  {
    MenuFunction2<THandler> mf(handler, name, desc);
    return mf;
  }

  #define CREATE_MENUFUNCTION(name, func, desc) \
    const char menuFuncName_##func[] PROGMEM = #func; \
    const char menuFuncDesc_##func[] PROGMEM = desc; \
    auto name = createMenuFunction(func, menuFuncName_##func, menuFuncDesc_##func)

  class MFWrapper2
  {
  public:

  };

  /*
  template<> class MenuFunction<void, int> : public MenuFunction<void, int>
  {
  protected:
    virtual void handleCommand(IMenu::Parameters p) override
    {
      handler(0);
    }
  public:
    //MenuFunction(_handler)
  };
  */
}
