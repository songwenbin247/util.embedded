#include "Console.h"
#include "fact/Menu.h"
#include "fact/PropertyMenuCommand.h"

namespace FactUtilEmbedded
{
  const char PROPERTYMENUCMD_GET[] PROGMEM = "get";
  const char PROPERTYMENUCMD_SET[] PROGMEM = "set";

#if defined(CONSOLE_FEATURE_ENHANCED_CHARPROCESSOR)
  bool PropertyMenuCommandBase::processInput(Console* console, char received)
  {
    return false;
  }
#endif

  void GetPropertyMenuCommand::handleCommand(Parameters p)
  {
    MENU_DECLARE_COUT;
    
    uint8_t i = 0;
    
    if(p.count == 0)
    {
      // TODO: get a foreach style iterator going for buffers - look at std/boost
      // and copy theirs
      for(; i < properties.getSize(); i++)
      {
        auto item = properties[i];
        
        cout << F("  ") << item->getName();
        cout.println();
      }
    }
    else if(p.count == 1)
    {
      const char* name = *p.parameters;
      
      for(; i < properties.getSize(); i++)
      {
        auto item = properties[i];
        const __FlashStringHelper* _itemName = item->getName();
        auto itemName = reinterpret_cast<const char*>(_itemName);
        
        if(strcmp_P(name, itemName) == 0)
        {
          item->get(cout);
          cout.println();
        }
      }
    }
  }
  
  
  
  void SetPropertyMenuCommand::handleCommand(Parameters p)
  {
    MENU_DECLARE_COUT;
    
    uint8_t i = 0;
    
    if(p.count == 2)
    {
      const char* name = p.parameters[0];
      const char* value = p.parameters[1];
      
      for(; i < properties.getSize(); i++)
      {
        auto item = properties[i];
        const __FlashStringHelper* _itemName = item->getName();
        auto itemName = reinterpret_cast<const char*>(_itemName);
        
        if(strcmp_P(name, itemName) == 0)
          item->set(value);
      }
    }
  }
}
