// $Id$

#include "Smart_Proxy_Impl.h"

ACE_CString Smart_Test_Proxy::fake_ior_ ("This_is_my_fake_ior");

Smart_Test_Factory::Smart_Test_Factory (void)
{
  ACE_DEBUG ((LM_DEBUG,
              "Smart_Test_Factory\n"));
}

Test_ptr
Smart_Test_Factory::create_proxy (Test_ptr proxy
                                  ACE_ENV_ARG_DECL_NOT_USED)
 {
   ACE_DEBUG ((LM_DEBUG,
               "create_smart_proxy\n"));

   if (CORBA::is_nil (proxy) == 0)
       ACE_NEW_RETURN (proxy, Smart_Test_Proxy (proxy), 0);

   return proxy;

 }

Smart_Test_Proxy::Smart_Test_Proxy (Test_ptr proxy)
  : TAO_Smart_Proxy_Base (proxy)
{
}

bool
Smart_Test_Proxy::can_convert_to_ior (void) const
{
  // Even though a smart proxy is local, this one can be stringified
  return true;
}

char*
Smart_Test_Proxy::convert_to_ior (bool,
                                  const char*) const
{
  // If this implementation wasn't provided, the ORB would provide
  // a stringified representation of this object.
  return CORBA::string_dup (fake_ior_.c_str ());
}

CORBA::Short
Smart_Test_Proxy::method (CORBA::Short boo
                          ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Test::Oops))
{
  ACE_DEBUG ((LM_DEBUG,
              "Yahoo, I am smart\n"));

  CORBA::Short retval = 0;
  ACE_TRY
    {
      retval = TAO_Test_Smart_Proxy_Base::method (boo
                                                  ACE_ENV_ARG_PARAMETER);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (Test::Oops, reason)
    {
      ACE_PRINT_EXCEPTION (reason,
                           "User Exception");
      return -1;
    }
  ACE_ENDTRY;

  return retval;
}

const ACE_CString&
Smart_Test_Proxy::fake_ior (void)
{
  return fake_ior_;
}
