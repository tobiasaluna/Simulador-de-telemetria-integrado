const connectBtn = document.getElementById("connectBtn");
const log = document.getElementById("log");

const tempEl = document.getElementById("temp");
const voltEl = document.getElementById("volt");
const rpmEl = document.getElementById("rpm");
const statusEl = document.getElementById("status");

function appendLog(text) {
  log.textContent += text;
  log.scrollTop = log.scrollHeight;
}

// Frame format:
// STX (0x02) + JSON + ETX (0x03) + 2 hex checksum + \n

function extractJson(frame) {
  const stx = frame.indexOf("\x02");
  const etx = frame.indexOf("\x03");

  if (stx === -1 || etx === -1) return null;
  return frame.substring(stx + 1, etx);
}

connectBtn.addEventListener("click", async () => {
  if (!("serial" in navigator)) {
    alert("Web Serial API not supported. Use Chrome/Edge.");
    return;
  }

  const port = await navigator.serial.requestPort();
  await port.open({ baudRate: 115200 });

  appendLog("Connected to serial port.\n");

  const decoder = new TextDecoderStream();
  port.readable.pipeTo(decoder.writable);

  const reader = decoder.readable.getReader();

  let buffer = "";

  while (true) {
    const { value, done } = await reader.read();
    if (done) break;

    buffer += value;

    let lines = buffer.split("\n");
    buffer = lines.pop(); // leftover

    for (let line of lines) {
      line += "\n";
      appendLog(line);

      const json = extractJson(line);
      if (!json) continue;

      try {
        const data = JSON.parse(json);

        tempEl.textContent = data.temp.toFixed(2);
        voltEl.textContent = data.volt.toFixed(2);
        rpmEl.textContent = data.rpm;
        statusEl.textContent = data.ok ? "OK" : "FAULT";

        statusEl.style.color = data.ok ? "lightgreen" : "red";
      } catch (err) {
        console.error("Invalid JSON", err);
      }
    }
  }
});
