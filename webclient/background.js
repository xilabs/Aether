chrome.app.runtime.onLaunched.addListener(function() {
  var happy = chrome.app.window.create('index.html', {
    'bounds': {
      'width': 900,
      'height': 500
    }
  });
});