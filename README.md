# Genesys GUI

### Compiling and running Genesys

Go to the Genesys directory:

`cd genesys`

Clean temporary files (optional - might be needed for subsequent builds):

`make -f Makefile CONF=Debug clean`

Build application:

`make -f Makefile CONF=Debug`

Run the executable:

`dist/Debug/GNU-Linux/20182-ongoing_regenesys_genericexpansiblesystemsimulator`
