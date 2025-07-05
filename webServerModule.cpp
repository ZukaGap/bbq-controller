#include <WebServer.h>
#include <WiFi.h>
#include "constants.h"

WebServer server(80);

extern float currentTemp;
extern bool fanState;
extern bool fanManualControl;

void handleRoot() {
  String ipAddress = "http://" + WiFi.localIP().toString();

  String html = "<!DOCTYPE html>";
  html += "<html><head>";
  html += "<title>ბარბექიუ კონტროლერი</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<meta charset='UTF-8'>";

  // Your existing CSS styles...
  html += "<style>";
  html += "* { margin: 0; padding: 0; box-sizing: border-box; }";
  html += "body { font-family: 'Segoe UI', Tahoma, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; padding: 20px; color: white; }";
  html += ".container { max-width: 600px; margin: 0 auto; background: rgba(255,255,255,0.1); backdrop-filter: blur(10px); border-radius: 20px; padding: 30px; box-shadow: 0 8px 32px rgba(0,0,0,0.3); }";
  html += "h1 { font-size: clamp(2rem, 5vw, 3rem); text-align: center; margin-bottom: 30px; text-shadow: 2px 2px 4px rgba(0,0,0,0.3); }";
  html += ".status-card { background: rgba(255,255,255,0.15); border-radius: 15px; padding: 25px; margin-bottom: 20px; border: 1px solid rgba(255,255,255,0.2); }";
  html += ".status-label { font-size: clamp(1.2rem, 4vw, 1.5rem); font-weight: bold; margin-bottom: 10px; opacity: 0.9; }";
  html += ".status-value { font-size: clamp(1.5rem, 5vw, 2rem); font-weight: bold; color: #FFD700; text-shadow: 1px 1px 2px rgba(0,0,0,0.5); }";
  html += ".loading { opacity: 0.7; animation: pulse 2s infinite; }";
  html += "@keyframes pulse { 0% { opacity: 0.7; } 50% { opacity: 1; } 100% { opacity: 0.7; } }";
  html += ".footer { text-align: center; margin-top: 30px; font-size: 0.9rem; opacity: 0.7; }";
  html += ".switch-container { display: flex; align-items: center; gap: 15px; }";
  html += ".switch { position: relative; display: inline-block; width: 60px; height: 34px; }";
  html += ".switch input { opacity: 0; width: 0; height: 0; }";
  html += ".slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; transition: .4s; border-radius: 34px; box-shadow: 0 2px 4px rgba(0,0,0,0.2); }";
  html += ".slider:before { position: absolute; content: ''; height: 26px; width: 26px; left: 4px; bottom: 4px; background-color: white; transition: .4s; border-radius: 50%; box-shadow: 0 2px 4px rgba(0,0,0,0.2); }";
  html += "input:checked + .slider { background-color: #4CAF50; }";
  html += "input:checked + .slider:before { transform: translateX(26px); }";
  html += ".switch-label { font-size: clamp(1.2rem, 4vw, 1.4rem); font-weight: bold; color: #FFD700; text-shadow: 1px 1px 2px rgba(0,0,0,0.5); }";
  html += "</style>";

  html += "<script src='https://cdn.jsdelivr.net/npm/qrious@4.0.2/dist/qrious.min.js'></script>";
  html += "</head><body>";

  html += "<div class='container'>";
  html += "<h1>🔥 ბარბექიუ კონტროლერი</h1>";

  html += "<div class='status-card'><div class='status-label'>🌡️ ტემპერატურა:</div><div class='status-value loading' id='temp'>Loading...</div></div>";
  html += "<div class='status-card'><div class='status-label'>💨 ჰაერის მიწოდება:</div><div class='status-value loading' id='fan'>Loading...</div></div>";

  html += "<div class='status-card'>";
  html += "<div class='status-label'>🎛️ ხელით კონტროლი:</div>";
  html += "<div class='switch-container'>";
  html += "<label class='switch'><input type='checkbox' id='fanSwitch' onchange='toggleFan()'><span class='slider'></span></label>";
  html += "<span class='switch-label loading' id='switchLabel'>Loading...</span>";
  html += "</div></div>";

  html += "<div class='status-card'>";
  html += "<div class='status-label'>📱 სწრაფი კავშირი (QR):</div>";
  html += "<canvas id='qrcode' style='margin-top:15px;'></canvas>";
  html += "<div style='margin-top:10px; font-size:0.9rem; word-break:break-all;'>" + ipAddress + "</div>";
  html += "</div>";

  html += "<div class='footer'>განახლდება ყოველ 2 წამში</div>";
  html += "</div>";

  html += "<script>";
  html += "function updateStatus() {";
  html += "fetch('/status').then(r=>r.json()).then(data=>{";
  html += "document.getElementById('temp').innerText = data.temperature + '°C';";
  html += "document.getElementById('fan').innerText = data.fan;";
  html += "const switchEl = document.getElementById('fanSwitch');";
  html += "const switchLabelEl = document.getElementById('switchLabel');";
  html += "switchEl.checked = data.manualControl;";
  html += "switchLabelEl.innerText = data.manualControl ? 'ჩართულია' : 'გამორთულია';";
  html += "document.getElementById('temp').classList.remove('loading');";
  html += "document.getElementById('fan').classList.remove('loading');";
  html += "switchLabelEl.classList.remove('loading');";
  html += "});}";
  
  html += "function toggleFan(){";
  html += "const isOn=document.getElementById('fanSwitch').checked;";
  html += "fetch('/toggle',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({fanControl:isOn})})";
  html += ".then(r=>r.json()).then(data=>{";
  html += "document.getElementById('switchLabel').innerText=data.status;";
  html += "setTimeout(updateStatus,500);";
  html += "});}";

  html += "updateStatus();";
  html += "setInterval(updateStatus,2000);";

  html += "const qr=new QRious({element:document.getElementById('qrcode'),value:'" + ipAddress + "',size:150});";
  html += "</script></body></html>";

  server.send(200, "text/html", html);
}

void handleStatus() {
  String json = "{";
  json += "\"temperature\":" + String(currentTemp, 2) + ",";
  json += "\"fan\":\"" + String(fanState ? "ჩართულია" : "გამორთულია") + "\",";
  json += "\"manualControl\":" + String(fanManualControl ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}

void handleToggleFan() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    fanManualControl = body.indexOf("\"fanControl\":true") != -1;
    String json = "{\"status\":\"" + String(fanManualControl ? "ჩართულია" : "გამორთულია") + "\",\"success\":true}";
    server.send(200, "application/json", json);
  } else {
    server.send(400, "application/json", "{\"error\":\"Invalid request\"}");
  }
}

void setupWebServer() {
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/toggle", HTTP_POST, handleToggleFan);
  server.begin();
}
