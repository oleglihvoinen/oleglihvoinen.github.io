

### 🧠 ChatBuddy-AI — Your Personal AI Chat Companion

ChatBuddy-AI is an open-source chatbot project that brings together natural language processing, web interface simplicity, and flexible backend architecture — creating a robust, developer-friendly chatbot you can adapt for many uses.

#### 📦 What ChatBuddy-AI Offers

* **Conversational AI backbone** using modern language models — enabling natural, context-aware dialogue.
* **Web-based UI** built with HTML/CSS/JS for lightweight, accessible interaction across devices.
* **Modular code structure** that separates backend logic (API or NLP engine) from the frontend interface, making customization and extension easier.
* **Ease of deployment** — run locally or deploy on a server; dependencies managed via a requirements file.
* **Flexibility for use-cases**: personal assistant, FAQ bot, content-based Q&A, or prototype for larger AI-powered apps.

---

### 🔧 Key Technologies & Design Choices

| Layer / Component          | Tech / Pattern                                                                    |
| -------------------------- | --------------------------------------------------------------------------------- |
| NLP / Chat Engine          | Python + modern LLM (or configurable model)                                       |
| Frontend UI                | HTML, CSS, JavaScript (lightweight web interface)                                 |
| API / Backend              | Python web server (e.g. FastAPI / Flask or simple HTTP)                           |
| Modularity & Extensibility | Decoupled backend & frontend — ease of swapping components                        |
| Deployment                 | Single-command or minimal-setup startup; `requirements.txt` used for dependencies |

---

### 🚀 Why This Project Matters

In a world increasingly powered by AI, ChatBuddy-AI serves as a **foundation** — not a finished product. It’s perfect for developers and enthusiasts who want to:

* Experiment with LLM-based chatbots without heavy overhead
* Learn how to integrate NLP backends with web front-ends
* Prototype assistants, Q&A bots or knowledge-base interfaces quickly
* Build something custom (e.g. domain-specific chatbot, internal tool, personal helper) without starting from scratch

Because it's open-source and modular, you can adapt ChatBuddy-AI to many scenarios: from internal documentation bots to content-driven chat assistants, or even as a base for more advanced AI-powered tools.

---

### 📝 How to Get Started

1. **Clone the repo**

   ```bash
   git clone https://github.com/oleglihvoinen/chatbuddy-ai.git
   cd chatbuddy-ai
   ```

2. **Install dependencies**

   ```bash
   pip install -r requirements.txt
   ```

3. **Run the backend/chat server**

Server:
 ```bash
cd server
npm install
# .env example:
# PORT=5001
# MONGO_URI=mongodb://localhost:27017/chatbuddy
# JWT_SECRET=supersecret
# OLLAMA_BASE_URL=http://localhost:11434
npm run dev
```
Server will run on `http://localhost:5001`.

Client:
Open a new terminal
```bash
cd client
npm install
npm run dev
```
Client will run on `http://localhost:5173` (Vite default).

> Ensure **Ollama** is running (`ollama serve`) and that you've pulled your chosen model, e.g. `ollama pull llama3`.

---

4. **Open the web frontend** in your browser — start chatting!

5. **Customize or extend**: swap the language model, add custom pre- or post-processing, integrate with other services, or embed in existing projects.

---

### 🌱 What’s Next — Ideas & Extensions

* Add support for **context-memory** — remember previous conversation for longer dialogs
* Provide **plugin interface** (e.g. call external APIs, perform tasks, fetch data)
* Use **database or vector store** for persistent knowledge base and retrieval-augmented responses
* Extend UI: mobile-friendly design, theming, or embedding into other web apps
* Deploy as a microservice — make ChatBuddy-AI accessible via a REST API or embed into larger systems

---

### ✅ Final Thoughts

ChatBuddy-AI isn’t just a simple demo — it’s a **flexible base** for prototyping, integration testing, and product development. Whether you want to prototype AI-powered chat, build an internal tool, or implement full-stack AI integration, this project gives you a clean and extendable starting point.

## 🎥 Video Demo

[👉 Watch the project running here] (https://youtu.be/4zVHcufBS-8)
