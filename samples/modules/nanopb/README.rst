.. _nanopb_sample:

Nanopb sample
#############

Overview
********

A simple protocol buffer sample using Nanopb for serializing structured data
to platform independent raw buffers or streams.


Requirements
************

Nanopb uses the protocol buffer compiler to generate source and header files,
make sure the ``protoc`` executable is installed and available.

.. tabs::

   .. group-tab:: Ubuntu

      Use ``apt`` to install dependency:

         .. code-block:: shell

            sudo apt install protobuf-compiler

   .. group-tab:: macOS

      Use ``brew`` to install dependency:

         .. code-block:: shell

            brew install protobuf

   .. group-tab:: Windows

      Use ``choco`` to install dependency:

         .. code-block:: shell

            choco install protoc


Additionally Nanopb is an optional module and needs to be added explicitly to the workspace:

.. code-block:: shell

   west config manifest.project-filter -- +nanopb
   west update


Building and Running
********************

This application can be built as follows:

.. zephyr-app-commands::
   :zephyr-app: samples/modules/nanopb
   :host-os: unix
   :board: qemu_x86
   :goals: run
   :compact:
