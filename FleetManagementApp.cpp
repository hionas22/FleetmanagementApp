// Fleet Management software
// Version 2.0
//Last Updated 4/14/2026 7/30/2022
//Nicholas Hionas

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Number One Software Solutions LLC</title>
  <style>
    * { box-sizing: border-box; }
    body {
      margin: 0;
      font-family: Arial, Helvetica, sans-serif;
      background: linear-gradient(180deg, #081120 0%, #0b1730 100%);
      color: #f8fafc;
      line-height: 1.6;
    }
    .wrap {
      max-width: 1100px;
      margin: 0 auto;
      padding: 24px;
    }
    .hero {
      background: linear-gradient(135deg, #0f1b33, #162746 55%, #1d3557);
      border: 1px solid rgba(148, 163, 184, 0.18);
      border-radius: 24px;
      padding: 40px 28px;
      margin-top: 24px;
      box-shadow: 0 20px 50px rgba(0, 0, 0, 0.28);
    }
    .badge {
      display: inline-block;
      padding: 8px 14px;
      border-radius: 999px;
      background: rgba(56, 189, 248, 0.12);
      border: 1px solid rgba(56, 189, 248, 0.22);
      color: #dbeafe;
      font-size: 13px;
      letter-spacing: 0.3px;
      margin-bottom: 18px;
    }
    .hero-grid {
      display: grid;
      grid-template-columns: 1.3fr 0.9fr;
      gap: 24px;
      align-items: center;
    }
    h1, h2, h3, p { margin-top: 0; }
    h1 {
      font-size: 48px;
      line-height: 1.05;
      margin-bottom: 14px;
      color: #f8fafc;
    }
    h2, h3 { color: #f8fafc; }
    .subtext {
      color: #d6e3f1;
      max-width: 720px;
      font-size: 18px;
    }
    .logo-box {
      text-align: center;
      background: rgba(255,255,255,0.05);
      border: 1px solid rgba(148, 163, 184, 0.16);
      border-radius: 20px;
      padding: 24px;
      box-shadow: inset 0 1px 0 rgba(255,255,255,0.04);
    }
    .logo-box img {
      max-width: 240px;
      width: 100%;
      height: auto;
      border-radius: 12px;
      display: block;
      margin: 0 auto 16px;
    }
    .contact-row, .services, .cards {
      display: flex;
      flex-wrap: wrap;
      gap: 12px;
    }
    .chip, .contact-pill {
      background: rgba(255,255,255,0.08);
      border: 1px solid rgba(148, 163, 184, 0.18);
      color: #f8fafc;
      padding: 10px 14px;
      border-radius: 999px;
      text-decoration: none;
      font-size: 14px;
      transition: 0.2s ease;
    }
    .chip:hover, .contact-pill:hover {
      background: rgba(56, 189, 248, 0.14);
      border-color: rgba(56, 189, 248, 0.28);
    }
    .section {
      margin-top: 28px;
      background: rgba(9, 18, 34, 0.58);
      border: 1px solid rgba(148, 163, 184, 0.12);
      border-radius: 22px;
      padding: 24px;
      box-shadow: 0 14px 34px rgba(0, 0, 0, 0.18);
    }
    .section-title {
      font-size: 30px;
      margin-bottom: 16px;
      color: #f8fafc;
    }
    .cards {
      gap: 18px;
    }
    .card {
      flex: 1 1 300px;
      background: linear-gradient(180deg, rgba(255,255,255,0.06), rgba(255,255,255,0.03));
      border: 1px solid rgba(148, 163, 184, 0.14);
      border-radius: 20px;
      padding: 24px;
      box-shadow: inset 0 1px 0 rgba(255,255,255,0.03);
    }
    .card h3 {
      font-size: 22px;
      margin-bottom: 8px;
      color: #e0f2fe;
    }
    ul {
      padding-left: 18px;
      margin-bottom: 0;
    }
    li { margin-bottom: 10px; color: #dbeafe; }
    .muted { color: #c9d8ea; }
    .cta {
      text-align: center;
      background: linear-gradient(135deg, #13233f, #17365d);
      border: 1px solid rgba(148, 163, 184, 0.18);
      border-radius: 22px;
      padding: 34px 24px;
      margin: 32px 0;
      box-shadow: 0 18px 40px rgba(0, 0, 0, 0.22);
    }
    .btn {
      display: inline-block;
      margin-top: 10px;
      background: linear-gradient(135deg, #38bdf8, #60a5fa);
      color: #06111f;
      text-decoration: none;
      padding: 12px 18px;
      border-radius: 999px;
      font-weight: bold;
      box-shadow: 0 10px 24px rgba(56, 189, 248, 0.24);
    }
    .btn:hover {
      filter: brightness(1.05);
    }
    @media (max-width: 800px) {
      .hero-grid { grid-template-columns: 1fr; }
      h1 { font-size: 36px; }
      .subtext { font-size: 16px; }
    }
  </style>
</head>
<body>
  <div class="wrap">
    <section class="hero">
      <div class="hero-grid">
        <div>
          <div class="badge">Business Consulting • Computer IT • Software Solutions</div>
          <h1>Number One Software Solutions LLC</h1>
          <p class="subtext">
            Helping businesses improve operations, solve IT problems, and implement practical software solutions that save time, reduce inefficiencies, and support growth.
          </p>

          <div class="contact-row" style="margin-top: 20px;">
            <a class="contact-pill" href="tel:+18563408663">856-340-8663</a>
            <a class="contact-pill" href="mailto:nhionas2001@gmail.com">nhionas2001@gmail.com</a>
            <span class="contact-pill">Beverly Hills, FL</span>
          </div>
        </div>

        <div class="logo-box">
          <img src="YOUR-LOGO-URL-HERE" alt="Number One Software Solutions LLC Logo" />
          <p class="muted" style="margin-bottom:0;">Custom software, IT support, business systems, and consulting for growing companies.</p>
        </div>
      </div>
    </section>

    <section class="section">
      <h2 class="section-title">Services</h2>
      <div class="services">
        <span class="chip">Business Consulting</span>
        <span class="chip">IT Support</span>
        <span class="chip">Custom Software Solutions</span>
        <span class="chip">Workflow Automation</span>
        <span class="chip">Systems Setup</span>
        <span class="chip">Process Optimization</span>
        <span class="chip">Operations Improvement</span>
        <span class="chip">Technical Troubleshooting</span>
      </div>
    </section>

    <section class="section">
      <h2 class="section-title">What We Help With</h2>
      <div class="cards">
        <div class="card">
          <h3>Business Consulting</h3>
          <ul>
            <li>Improve daily operations and reduce bottlenecks</li>
            <li>Build better systems for inventory, workflows, and staff coordination</li>
            <li>Identify inefficiencies and create practical solutions</li>
          </ul>
        </div>

        <div class="card">
          <h3>Computer IT</h3>
          <ul>
            <li>Troubleshoot hardware, software, and network issues</li>
            <li>Support business technology setup and maintenance</li>
            <li>Help keep systems reliable, secure, and easy to use</li>
          </ul>
        </div>

        <div class="card">
          <h3>Software Solutions</h3>
          <ul>
            <li>Create custom tools to simplify business processes</li>
            <li>Automate repetitive tasks and improve reporting</li>
            <li>Implement systems that help teams work faster and smarter</li>
          </ul>
        </div>
      </div>
    </section>

    <section class="cta">
      <h2>Need help improving your business systems or IT setup?</h2>
      <p class="muted">Let’s talk about how Number One Software Solutions LLC can support your business.</p>
      <a class="btn" href="mailto:nhionas2001@gmail.com">Request a Consultation</a>
    </section>
  </div>
</body>
</html>
