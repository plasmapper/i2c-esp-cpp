I2C Component
=============

.. |COMPONENT| replace:: i2c

.. |ESP_IDF_VERSION| replace:: 5.3
   
.. |VERSION| replace:: 1.0.1

.. include:: ../../../installation.rst

.. include:: ../../../sdkconfig_common.rst

Features
--------

1. :cpp:class:`PL::I2C` - an I2C interface class that is used for several I2C controllers that use the same interface.
2. :cpp:class:`PL::I2CController` - an I2C controller class that is used for communication with a single I2C target.
   :cpp:func:`PL::I2CController::Initialize` initializes the I2C interface (if it has not been previously initialized) and the I2C controller.
   :cpp:func:`PL::I2CController::Read` performs an I2C read operation. :cpp:func:`PL::I2CController::Write` performs an I2C write operation.
   Operation timeout can be get and set using :cpp:func:`PL::I2CController::GetTimeout` and :cpp:func:`PL::I2CController::SetTimeout`.

I2C target is not implemented yet.

Thread safety
-------------

Class method thread safety is implemented by having the :cpp:class:`PL::Lockable` as a base class and creating the class object lock guard at the beginning of the methods.

::cpp:func:`PL::I2CController::Initialize`, ::cpp:func:`PL::I2CController::Read` and :cpp:func:`PL::I2CController::Write` lock both
the :cpp:class:`PL::I2CController` and the :cpp:class:`PL::I2C` objects for the duration of the method. 

Examples
--------
| `I2C controller <https://components.espressif.com/components/plasmapper/pl_i2c/versions/1.0.1/examples/i2c_controller>`_

API reference
-------------

.. toctree::
  
  api/i2c
  api/i2c_controller