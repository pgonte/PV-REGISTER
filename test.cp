<!DOCTYPE html>
<html lang="en">
<head>
<!-- skill:chrome -->
<style>
/* Credit line — bottom-right */
.design-ui-credit {
  position: fixed;
  bottom: 12px;
  right: 12px;
  font: 11px/1 system-ui, sans-serif;
  color: rgba(128,128,128,0.5);
  pointer-events: none;
  z-index: 2147483647;
  transition: opacity 0.4s ease;
  user-select: none;
  letter-spacing: 0.02em;
}

/* Hide chrome on touch devices */
@media (hover: none) {
  .design-ui-credit { display: none; }
}

/* Print fixes */
@media print {
  * {
    transition: none !important;
    animation: none !important;
    box-shadow: none !important;
  }
  body {
    print-color-adjust: exact;
    -webkit-print-color-adjust: exact;
  }
  .design-ui-credit { display: none !important; }
}

</style>
<script>
(function () {
    // Design-ui pages are single compositions, so the whole body is editable.
    function markEditable() {
        document.body.classList.add('artifact-editable');
    }

    // Credit badge with idle-fade. Hover devices only.
    function initChromeUI() {
        if (!matchMedia('(hover: hover)').matches) return;

        var credit = document.createElement('div');
        credit.className = 'design-ui-credit';
        credit.setAttribute('aria-hidden', 'true');
        credit.innerHTML = '\u{1F49C} by ClickUp Brain';
        document.body.appendChild(credit);

        var timer = null;
        var fade = function (out) { credit.style.opacity = out ? '0' : ''; };
        fade(true);
        var show = function () {
            fade(false);
            clearTimeout(timer);
            timer = setTimeout(function () { fade(true); }, 3000);
        };
        document.addEventListener('mousemove', show);
        show();
    }

    function init() {
        markEditable();
        initChromeUI();
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', init);
    } else {
        init();
    }
})();

</script>
<!-- /skill:chrome -->
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>PV Training Register</title>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
<script src="https://alcdn.msauth.net/browser/2.38.0/js/msal-browser.min.js"></script>
<style>
  *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

  :root {
    --primary: oklch(45% 0.18 275);
    --primary-light: oklch(92% 0.04 275);
    --primary-hover: oklch(38% 0.18 275);
    --neutral-50: oklch(98% 0.005 275);
    --neutral-100: oklch(95% 0.008 275);
    --neutral-200: oklch(90% 0.01 275);
    --neutral-300: oklch(82% 0.01 275);
    --neutral-500: oklch(55% 0.01 275);
    --neutral-700: oklch(35% 0.012 275);
    --neutral-900: oklch(18% 0.015 275);
    --success: oklch(55% 0.16 145);
    --success-bg: oklch(92% 0.04 145);
    --error: oklch(55% 0.2 25);
    --error-bg: oklch(94% 0.03 25);
    --surface: oklch(99% 0.003 275);
    --ease-out-expo: cubic-bezier(0.16, 1, 0.3, 1);
  }

  body {
    font-family: 'Inter', system-ui, sans-serif;
    background: var(--neutral-100);
    color: var(--neutral-900);
    line-height: 1.5;
    min-height: 100vh;
    font-optical-sizing: auto;
  }

  .page {
    max-width: 900px;
    margin: 0 auto;
    padding: 32px 24px 64px;
  }

  header {
    text-align: center;
    margin-bottom: 40px;
  }

  header h1 {
    font-size: 1.75rem;
    font-weight: 700;
    color: var(--neutral-900);
    letter-spacing: -0.02em;
    text-wrap: balance;
  }

  header p {
    font-size: 0.875rem;
    color: var(--neutral-500);
    margin-top: 8px;
  }

  .auth-section {
    background: var(--surface);
    border: 1px solid var(--neutral-200);
    border-radius: 16px;
    padding: 48px 32px;
    text-align: center;
    margin-bottom: 32px;
  }

  .auth-section h2 {
    font-size: 1.125rem;
    font-weight: 600;
    margin-bottom: 8px;
  }

  .auth-section p {
    font-size: 0.875rem;
    color: var(--neutral-500);
    margin-bottom: 24px;
    max-width: 45ch;
    margin-inline: auto;
  }

  .btn-microsoft {
    display: inline-flex;
    align-items: center;
    gap: 10px;
    background: var(--neutral-900);
    color: white;
    border: none;
    border-radius: 10px;
    padding: 14px 28px;
    font-size: 0.9375rem;
    font-weight: 600;
    font-family: inherit;
    cursor: pointer;
    transition: transform 100ms var(--ease-out-expo), opacity 150ms;
  }

  .btn-microsoft:hover { opacity: 0.9; }
  .btn-microsoft:active { transform: scale(0.97); }

  .btn-microsoft svg { width: 20px; height: 20px; }

  .user-bar {
    display: flex;
    align-items: center;
    justify-content: space-between;
    background: var(--success-bg);
    border: 1px solid oklch(80% 0.08 145);
    border-radius: 10px;
    padding: 12px 20px;
    margin-bottom: 32px;
    font-size: 0.875rem;
  }

  .user-bar span { color: oklch(30% 0.08 145); font-weight: 500; }

  .btn-signout {
    background: transparent;
    border: 1px solid oklch(70% 0.08 145);
    border-radius: 6px;
    padding: 4px 12px;
    font-size: 0.75rem;
    font-weight: 500;
    color: oklch(35% 0.08 145);
    cursor: pointer;
    font-family: inherit;
  }

  .register-form {
    background: var(--surface);
    border: 1px solid var(--neutral-200);
    border-radius: 16px;
    padding: 32px;
    margin-bottom: 32px;
  }

  .form-row {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 20px;
    margin-bottom: 24px;
  }

  @media (max-width: 600px) {
    .form-row { grid-template-columns: 1fr; }
  }

  .field label {
    display: block;
    font-size: 0.8125rem;
    font-weight: 600;
    color: var(--neutral-700);
    margin-bottom: 6px;
    text-transform: uppercase;
    letter-spacing: 0.06em;
  }

  .field input {
    width: 100%;
    padding: 12px 16px;
    border: 1px solid var(--neutral-200);
    border-radius: 10px;
    font-size: 1rem;
    font-family: inherit;
    color: var(--neutral-900);
    background: var(--neutral-50);
    transition: border-color 200ms var(--ease-out-expo), box-shadow 200ms var(--ease-out-expo);
  }

  .field input:focus {
    outline: none;
    border-color: var(--primary);
    box-shadow: 0 0 0 3px oklch(45% 0.18 275 / 0.12);
  }

  .field input::placeholder { color: var(--neutral-300); }

  .signature-section { margin-bottom: 24px; }

  .signature-section label {
    display: block;
    font-size: 0.8125rem;
    font-weight: 600;
    color: var(--neutral-700);
    margin-bottom: 6px;
    text-transform: uppercase;
    letter-spacing: 0.06em;
  }

  .signature-wrapper {
    position: relative;
    border: 1px dashed var(--neutral-300);
    border-radius: 10px;
    background: var(--neutral-50);
    overflow: hidden;
  }

  .signature-wrapper.active { border-color: var(--primary); border-style: solid; }

  #signatureCanvas {
    display: block;
    width: 100%;
    height: 140px;
    cursor: crosshair;
    touch-action: none;
  }

  .signature-hint {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    font-size: 0.8125rem;
    color: var(--neutral-300);
    pointer-events: none;
    transition: opacity 200ms var(--ease-out-expo);
  }

  .signature-wrapper.has-content .signature-hint { opacity: 0; }

  .clear-sig {
    position: absolute;
    top: 8px;
    right: 8px;
    background: var(--neutral-200);
    border: none;
    border-radius: 6px;
    padding: 4px 10px;
    font-size: 0.75rem;
    font-weight: 500;
    color: var(--neutral-700);
    cursor: pointer;
    opacity: 0;
    transition: opacity 150ms var(--ease-out-expo);
  }

  .signature-wrapper.has-content .clear-sig { opacity: 1; }
  .clear-sig:hover { background: var(--neutral-300); }

  .form-actions {
    display: flex;
    gap: 12px;
    align-items: center;
  }

  .btn-primary {
    background: var(--primary);
    color: white;
    border: none;
    border-radius: 10px;
    padding: 12px 28px;
    font-size: 0.9375rem;
    font-weight: 600;
    font-family: inherit;
    cursor: pointer;
    transition: background 150ms var(--ease-out-expo), transform 100ms var(--ease-out-expo);
  }

  .btn-primary:hover { background: var(--primary-hover); }
  .btn-primary:active { transform: scale(0.97); }
  .btn-primary:disabled { opacity: 0.5; cursor: not-allowed; transform: none; }

  .btn-secondary {
    background: transparent;
    color: var(--neutral-500);
    border: 1px solid var(--neutral-200);
    border-radius: 10px;
    padding: 12px 20px;
    font-size: 0.875rem;
    font-weight: 500;
    font-family: inherit;
    cursor: pointer;
    transition: border-color 150ms var(--ease-out-expo), color 150ms var(--ease-out-expo);
  }

  .btn-secondary:hover { border-color: var(--neutral-300); color: var(--neutral-700); }

  .toast {
    position: fixed;
    bottom: 24px;
    left: 50%;
    transform: translateX(-50%) translateY(100px);
    padding: 12px 24px;
    border-radius: 10px;
    font-size: 0.875rem;
    font-weight: 500;
    opacity: 0;
    transition: transform 400ms var(--ease-out-expo), opacity 300ms var(--ease-out-expo);
    z-index: 100;
  }

  .toast.success { background: var(--success-bg); border: 1px solid oklch(75% 0.1 145); color: oklch(30% 0.1 145); }
  .toast.error { background: var(--error-bg); border: 1px solid oklch(75% 0.1 25); color: oklch(30% 0.1 25); }
  .toast.visible { transform: translateX(-50%) translateY(0); opacity: 1; }

  .records-section {
    background: var(--surface);
    border: 1px solid var(--neutral-200);
    border-radius: 16px;
    overflow: hidden;
  }

  .records-header {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 24px 32px 16px;
  }

  .records-header h2 { font-size: 1.125rem; font-weight: 600; }

  .record-count {
    font-size: 0.8125rem;
    color: var(--neutral-500);
    font-weight: 500;
    background: var(--neutral-100);
    padding: 4px 12px;
    border-radius: 20px;
  }

  .export-row {
    display: flex;
    gap: 8px;
    padding: 0 32px 16px;
    flex-wrap: wrap;
  }

  .btn-export {
    background: var(--primary-light);
    color: var(--primary);
    border: none;
    border-radius: 8px;
    padding: 8px 16px;
    font-size: 0.8125rem;
    font-weight: 600;
    font-family: inherit;
    cursor: pointer;
    transition: background 150ms var(--ease-out-expo);
  }

  .btn-export:hover { background: oklch(88% 0.06 275); }
  .btn-export:disabled { opacity: 0.4; cursor: not-allowed; }

  .records-table {
    width: 100%;
    border-collapse: collapse;
  }

  .records-table thead th {
    text-align: left;
    font-size: 0.75rem;
    font-weight: 600;
    text-transform: uppercase;
    letter-spacing: 0.06em;
    color: var(--neutral-500);
    padding: 12px 32px;
    border-top: 1px solid var(--neutral-200);
    border-bottom: 1px solid var(--neutral-200);
    background: var(--neutral-50);
  }

  .records-table tbody tr { transition: background 100ms var(--ease-out-expo); }
  .records-table tbody tr:hover { background: var(--neutral-50); }

  .records-table tbody td {
    padding: 14px 32px;
    font-size: 0.875rem;
    border-bottom: 1px solid var(--neutral-100);
    vertical-align: middle;
  }

  .records-table tbody td:first-child {
    font-variant-numeric: tabular-nums;
    color: var(--neutral-500);
    width: 40px;
  }

  .sig-preview { height: 32px; border-radius: 4px; }

  .empty-state {
    text-align: center;
    padding: 48px 32px;
    color: var(--neutral-300);
    font-size: 0.9375rem;
  }

  .timestamp-col {
    font-size: 0.8125rem;
    color: var(--neutral-500);
    font-variant-numeric: tabular-nums;
  }

  .loading-spinner {
    display: inline-block;
    width: 16px;
    height: 16px;
    border: 2px solid var(--neutral-200);
    border-top-color: var(--primary);
    border-radius: 50%;
    animation: spin 600ms linear infinite;
    margin-right: 8px;
    vertical-align: middle;
  }

  @keyframes spin { to { transform: rotate(360deg); } }

  .hidden { display: none !important; }

  @media print {
    body { background: white; }
    .register-form, .export-row, .form-actions, .auth-section, .user-bar { display: none; }
    .records-section { border: none; }
    .page { padding: 0; max-width: none; }
    header { margin-bottom: 24px; }
  }
</style>
</head>
<body>
<div class="page">
  <header>
    <h1>Pharmacovigilance Training Register</h1>
    <p>Please sign in with your Microsoft account, then register your attendance below</p>
  </header>

  <div class="auth-section" id="authSection">
    <h2>Sign in to continue</h2>
    <p>Use your ACRN Health Microsoft account to access the training register</p>
    <button class="btn-microsoft" id="loginBtn">
      <svg viewBox="0 0 21 21" fill="none"><rect x="1" y="1" width="9" height="9" fill="#F25022"/><rect x="11" y="1" width="9" height="9" fill="#7FBA00"/><rect x="1" y="11" width="9" height="9" fill="#00A4EF"/><rect x="11" y="11" width="9" height="9" fill="#FFB900"/></svg>
      Sign in with Microsoft
    </button>
  </div>

  <div class="user-bar hidden" id="userBar">
    <span id="userName">Signed in</span>
    <button class="btn-signout" id="signoutBtn">Sign out</button>
  </div>

  <div class="register-form hidden" id="registerForm">
    <div class="form-row">
      <div class="field">
        <label for="nameInput">Full Name</label>
        <input type="text" id="nameInput" placeholder="e.g. John Moyo" autocomplete="off">
      </div>
      <div class="field">
        <label for="designationInput">Designation</label>
        <input type="text" id="designationInput" placeholder="e.g. Clinical Research Associate" autocomplete="off">
      </div>
    </div>

    <div class="signature-section">
      <label>Signature</label>
      <div class="signature-wrapper" id="sigWrapper">
        <canvas id="signatureCanvas"></canvas>
        <span class="signature-hint">Draw your signature here</span>
        <button class="clear-sig" id="clearSig">Clear</button>
      </div>
    </div>

    <div class="form-actions">
      <button class="btn-primary" id="submitBtn">Submit Entry</button>
      <button class="btn-secondary" id="resetBtn">Reset Form</button>
    </div>
  </div>

  <div class="records-section" id="recordsSection">
    <div class="records-header">
      <h2>Attendees</h2>
      <span class="record-count" id="recordCount">0 entries</span>
    </div>
    <div class="export-row">
      <button class="btn-export" id="exportCsv" disabled>Export CSV</button>
      <button class="btn-export" id="exportPdf" disabled>Print / PDF</button>
      <button class="btn-export" id="refreshBtn">Refresh</button>
    </div>
    <div id="tableContainer">
      <div class="empty-state" id="emptyState">Sign in to view and add entries.</div>
    </div>
  </div>
</div>

<div class="toast success" id="successToast">Entry saved to SharePoint</div>
<div class="toast error" id="errorToast">Something went wrong</div>

<script>
(function() {
  var CLIENT_ID = '7f6513f4-0363-48b6-a71d-a386abb56b51';
  var TENANT_ID = '32b780c8-6b81-4ae4-9403-56d535a6c5f1';
  var SITE_HOST = 'acrnhealth.sharepoint.com';
  var SITE_PATH = '/sites/PharmacovigilanceConsultants-SafeVigSolutions';
  var LIST_NAME = 'TRAINING';

  var GRAPH_BASE = 'https://graph.microsoft.com/v1.0';
  var SCOPES = ['Sites.ReadWrite.All'];

  var authSection = document.getElementById('authSection');
  var userBar = document.getElementById('userBar');
  var userNameEl = document.getElementById('userName');
  var registerForm = document.getElementById('registerForm');
  var loginBtn = document.getElementById('loginBtn');
  var signoutBtn = document.getElementById('signoutBtn');
  var canvas = document.getElementById('signatureCanvas');
  var ctx = canvas.getContext('2d');
  var wrapper = document.getElementById('sigWrapper');
  var nameInput = document.getElementById('nameInput');
  var designationInput = document.getElementById('designationInput');
  var submitBtn = document.getElementById('submitBtn');
  var resetBtn = document.getElementById('resetBtn');
  var clearSig = document.getElementById('clearSig');
  var exportCsv = document.getElementById('exportCsv');
  var exportPdf = document.getElementById('exportPdf');
  var refreshBtn = document.getElementById('refreshBtn');
  var tableContainer = document.getElementById('tableContainer');
  var recordCount = document.getElementById('recordCount');
  var successToast = document.getElementById('successToast');
  var errorToast = document.getElementById('errorToast');

  var msalInstance = null;
  var accessToken = null;
  var siteId = null;
  var listId = null;
  var isDrawing = false;
  var hasSignature = false;
  var records = [];

  var msalConfig = {
    auth: {
      clientId: CLIENT_ID,
      authority: 'https://login.microsoftonline.com/' + TENANT_ID,
      redirectUri: window.location.origin + window.location.pathname
    },
    cache: {
      cacheLocation: 'localStorage',
      storeAuthStateInCookie: false
    }
  };

  msalInstance = new msal.PublicClientApplication(msalConfig);

  msalInstance.initialize().then(function() {
    msalInstance.handleRedirectPromise().then(function(response) {
      if (response) {
        handleLoginSuccess(response);
      } else {
        var accounts = msalInstance.getAllAccounts();
        if (accounts.length > 0) {
          silentLogin(accounts[0]);
        }
      }
    });
  });

  function silentLogin(account) {
    msalInstance.acquireTokenSilent({ scopes: SCOPES, account: account }).then(function(response) {
      handleLoginSuccess(response);
    }).catch(function(e) {
      console.log('Silent login failed');
    });
  }

  function handleLoginSuccess(response) {
    accessToken = response.accessToken;
    var name = response.account.name || response.account.username;
    showLoggedIn(name);
    initSharePoint();
  }

  function showLoggedIn(name) {
    authSection.classList.add('hidden');
    userBar.classList.remove('hidden');
    registerForm.classList.remove('hidden');
    userNameEl.textContent = 'Signed in as ' + name;
  }

  loginBtn.addEventListener('click', function() {
    msalInstance.loginPopup({ scopes: SCOPES }).then(function(response) {
      handleLoginSuccess(response);
    }).catch(function(e) {
      showError('Login cancelled or failed');
    });
  });

  signoutBtn.addEventListener('click', function() {
    msalInstance.logoutPopup();
    authSection.classList.remove('hidden');
    userBar.classList.add('hidden');
    registerForm.classList.add('hidden');
    accessToken = null;
  });

  function graphGet(url) {
    return fetch(url, {
      headers: { 'Authorization': 'Bearer ' + accessToken, 'Content-Type': 'application/json' }
    }).then(function(resp) {
      if (!resp.ok) throw new Error('Graph API error: ' + resp.status);
      return resp.json();
    });
  }

  function graphPost(url, body) {
    return fetch(url, {
      method: 'POST',
      headers: { 'Authorization': 'Bearer ' + accessToken, 'Content-Type': 'application/json' },
      body: JSON.stringify(body)
    }).then(function(resp) {
      if (!resp.ok) throw new Error('Graph API error: ' + resp.status);
      return resp.json();
    });
  }

  function initSharePoint() {
    graphGet(GRAPH_BASE + '/sites/' + SITE_HOST + ':' + SITE_PATH).then(function(site) {
      siteId = site.id;
      return graphGet(GRAPH_BASE + '/sites/' + siteId + '/lists/' + LIST_NAME);
    }).then(function(list) {
      listId = list.id;
      return loadRecords();
    }).catch(function(e) {
      console.error('SharePoint init failed:', e);
      showError('Could not connect to SharePoint list. Check permissions.');
    });
  }

  function loadRecords() {
    return graphGet(GRAPH_BASE + '/sites/' + siteId + '/lists/' + listId + '/items?expand=fields&$top=500&$orderby=createdDateTime desc').then(function(data) {
      records = (data.value || []).map(function(item) {
        return {
          id: item.id,
          name: item.fields.Title || '',
          designation: item.fields.Designation || '',
          signature: item.fields.Signature || '',
          time: item.fields.SignedAt || new Date(item.createdDateTime).toLocaleString('en-GB', { day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit' })
        };
      }).reverse();
      updateUI();
    }).catch(function(e) {
      console.error('Failed to load records:', e);
      showError('Failed to load records from SharePoint');
    });
  }

  function addRecord(name, designation, signatureData) {
    var now = new Date();
    var time = now.toLocaleString('en-GB', { day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit' });

    var body = {
      fields: {
        Title: name,
        Designation: designation,
        Signature: signatureData,
        SignedAt: time
      }
    };

    submitBtn.disabled = true;
    submitBtn.innerHTML = '<span class="loading-spinner"></span>Saving...';

    graphPost(GRAPH_BASE + '/sites/' + siteId + '/lists/' + listId + '/items', body).then(function() {
      records.push({ name: name, designation: designation, signature: signatureData, time: time });
      updateUI();
      showSuccess('Entry saved to SharePoint');
      resetFormFields();
    }).catch(function(e) {
      console.error('Failed to save:', e);
      showError('Failed to save entry. Check list column names.');
    }).finally(function() {
      submitBtn.disabled = false;
      submitBtn.textContent = 'Submit Entry';
    });
  }

  function resizeCanvas() {
    var rect = canvas.getBoundingClientRect();
    var dpr = window.devicePixelRatio || 1;
    canvas.width = rect.width * dpr;
    canvas.height = rect.height * dpr;
    ctx.scale(dpr, dpr);
    ctx.lineCap = 'round';
    ctx.lineJoin = 'round';
    ctx.lineWidth = 2;
    ctx.strokeStyle = '#1a1a2e';
  }

  resizeCanvas();
  window.addEventListener('resize', function() { resizeCanvas(); hasSignature = false; wrapper.classList.remove('has-content'); });

  function getPos(e) {
    var rect = canvas.getBoundingClientRect();
    var clientX = e.touches ? e.touches[0].clientX : e.clientX;
    var clientY = e.touches ? e.touches[0].clientY : e.clientY;
    return { x: clientX - rect.left, y: clientY - rect.top };
  }

  function startDraw(e) { isDrawing = true; wrapper.classList.add('active'); var pos = getPos(e); ctx.beginPath(); ctx.moveTo(pos.x, pos.y); e.preventDefault(); }
  function draw(e) { if (!isDrawing) return; var pos = getPos(e); ctx.lineTo(pos.x, pos.y); ctx.stroke(); hasSignature = true; wrapper.classList.add('has-content'); e.preventDefault(); }
  function endDraw() { isDrawing = false; wrapper.classList.remove('active'); }

  canvas.addEventListener('mousedown', startDraw);
  canvas.addEventListener('mousemove', draw);
  canvas.addEventListener('mouseup', endDraw);
  canvas.addEventListener('mouseleave', endDraw);
  canvas.addEventListener('touchstart', startDraw, { passive: false });
  canvas.addEventListener('touchmove', draw, { passive: false });
  canvas.addEventListener('touchend', endDraw);

  clearSig.addEventListener('click', function() { ctx.clearRect(0, 0, canvas.width, canvas.height); hasSignature = false; wrapper.classList.remove('has-content'); });

  submitBtn.addEventListener('click', function() {
    var name = nameInput.value.trim();
    var designation = designationInput.value.trim();
    if (!name) { nameInput.focus(); return; }
    if (!designation) { designationInput.focus(); return; }
    if (!hasSignature) { showError('Please provide your signature'); return; }
    var sigData = canvas.toDataURL('image/png');
    addRecord(name, designation, sigData);
  });

  function resetFormFields() {
    nameInput.value = '';
    designationInput.value = '';
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    hasSignature = false;
    wrapper.classList.remove('has-content');
    nameInput.focus();
  }

  resetBtn.addEventListener('click', resetFormFields);

  refreshBtn.addEventListener('click', function() {
    if (accessToken && siteId && listId) loadRecords();
  });

  exportCsv.addEventListener('click', function() {
    if (records.length === 0) return;
    var csv = 'No,Name,Designation,Date/Time\n';
    records.forEach(function(r, i) {
      csv += (i + 1) + ',"' + r.name.replace(/"/g, '""') + '","' + r.designation.replace(/"/g, '""') + '","' + r.time + '"\n';
    });
    var blob = new Blob([csv], { type: 'text/csv' });
    var url = URL.createObjectURL(blob);
    var a = document.createElement('a');
    a.href = url;
    a.download = 'PV_Training_Register_' + new Date().toISOString().slice(0, 10) + '.csv';
    a.click();
    URL.revokeObjectURL(url);
  });

  exportPdf.addEventListener('click', function() { window.print(); });

  function updateUI() {
    var count = records.length;
    recordCount.textContent = count + (count === 1 ? ' entry' : ' entries');
    exportCsv.disabled = count === 0;
    exportPdf.disabled = count === 0;

    if (count === 0) {
      tableContainer.innerHTML = '<div class="empty-state">No entries yet. Be the first to sign in.</div>';
      return;
    }

    var html = '<table class="records-table"><thead><tr><th>#</th><th>Name</th><th>Designation</th><th>Signature</th><th>Time</th></tr></thead><tbody>';
    records.forEach(function(r, i) {
      var sigCell = (r.signature && r.signature.indexOf('data:image') === 0)
        ? '<img class="sig-preview" src="' + r.signature + '" alt="signature">'
        : '<span style="color:var(--neutral-300)">-</span>';
      html += '<tr><td>' + (i + 1) + '</td><td>' + escHtml(r.name) + '</td><td>' + escHtml(r.designation) + '</td><td>' + sigCell + '</td><td class="timestamp-col">' + escHtml(r.time) + '</td></tr>';
    });
    html += '</tbody></table>';
    tableContainer.innerHTML = html;
  }

  function escHtml(s) { var d = document.createElement('div'); d.textContent = s; return d.innerHTML; }

  function showSuccess(msg) {
    successToast.textContent = msg;
    successToast.classList.add('visible');
    setTimeout(function() { successToast.classList.remove('visible'); }, 3000);
  }

  function showError(msg) {
    errorToast.textContent = msg;
    errorToast.classList.add('visible');
    setTimeout(function() { errorToast.classList.remove('visible'); }, 4000);
  }

  updateUI();
})();
</script>
</body>
</html>
