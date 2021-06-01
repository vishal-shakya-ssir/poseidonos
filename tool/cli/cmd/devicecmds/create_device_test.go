package devicecmds_test

import (
	"bytes"
	"cli/cmd"
	"cli/cmd/testmgr"
	"log"
	"testing"
)

// This testing tests if the request is created well in JSON form from the command line.
func TestCreateDeviceCommandReq(t *testing.T) {

	// Command creation
	rootCmd := cmd.RootCmd

	// mj: For testing, I temporarily redirect log output to buffer.
	var buff bytes.Buffer
	log.SetOutput(&buff)
	log.SetFlags(0)

	// Execute the command to test with argument
	testmgr.ExecuteCommand(rootCmd, "device", "create", "--device-name", "dev0", "--num-blocks", "512", "--block-size", "4096", "--device-type", "uram", "--json-req")

	output := buff.String()
	output = output[:len(output)-1] // Remove the last n from output string
	expected := `{"command":"CREATEDEVICE","rid":"fromfakeclient","param":{"name":"dev0","num_blocks":512,"block_size":4096,"dev_type":"uram"}}`

	if expected != output {
		t.Errorf("Expected: %q Output: %q", expected, output)
	}
}