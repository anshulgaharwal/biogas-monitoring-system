// Firebase config (from Firebase Console → Web App)
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.22.2/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/9.22.2/firebase-database.js";

const firebaseConfig = {
  apiKey: "AIzaSyDru_8EuDzycD9koI5VP3yfySshoYa_X-s",
  authDomain: "sensormonitor-27136.firebaseapp.com",
  databaseURL: "https://sensormonitor-27136-default-rtdb.firebaseio.com",
  projectId: "sensormonitor-27136",
  storageBucket: "sensormonitor-27136.firebasestorage.app",
  messagingSenderId: "673725171032",
  appId: "1:673725171032:web:814b31f0f6aabf1489112d"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

onValue(ref(db, '/temperature'), (snapshot) => {
  document.getElementById('temp').innerText = `Temperature: ${snapshot.val()} °C`;
});
onValue(ref(db, '/humidity'), (snapshot) => {
  document.getElementById('hum').innerText = `Humidity: ${snapshot.val()} %`;
});
onValue(ref(db, '/ph'), (snapshot) => {
  document.getElementById('ph').innerText = `PH: ${snapshot.val() / 100}`;
});
