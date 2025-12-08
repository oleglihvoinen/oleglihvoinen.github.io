
Integrating FTIR Spectroscopy Data into ERP Workflows
---

Modern laboratories and manufacturing environments produce a huge amount of analytical data. Yet, most of this information remains **isolated** inside instruments — never making it into the organization's **ERP (Enterprise Resource Planning)** system, where it could drive quality decisions, traceability, and automation.

In this project, I built a complete workflow that connects **FTIR spectroscopy** data with an **ERP backend**, using Python as the bridge between scientific measurements and enterprise systems.

The result is an end-to-end pipeline capable of:

- Loading FTIR spectra  
- Preprocessing and smoothing  
- Detecting deviations from reference material  
- Projecting data with PCA  
- Classifying samples (PASS/FAIL or ML prediction)  
- Sending QC results into an ERP API  

---

# 🔬 What Is FTIR Spectroscopy?

**FTIR (Fourier-Transform Infrared Spectroscopy)** is a method for identifying chemical substances by measuring how they absorb infrared light.

Common uses include:

- Polymer identification  
- Incoming raw material quality checks  
- Contamination detection  
- Batch-to-batch consistency verification  

Each material has a **unique spectral fingerprint**, which can be compared against a reference spectrum.

---

# 🏭 Why Integrate FTIR with ERP?

ERP systems maintain:

- Material master data  
- Batch records  
- Supplier info  
- Manufacturing execution workflows  

However, FTIR results often stay locked inside software like OMNIC, Spectrum, or OPUS.

By integrating FTIR→ERP, organizations can:

- Approve or reject raw materials automatically  
- Trigger workflows based on spectral deviations  
- Generate QC reports without human entry  
- Improve traceability across the supply chain  
- Strengthen compliance with ISO & GMP standards  

---

# 🔧 System Architecture

Below is the data flow I implemented for this project:

![FTIR to ERP flow diagram](/assets/img/ftir_erp/ftir_erp_flow.png)

<small>Figure 1 — FTIR data pipeline from instrument to ERP backend.</small>

---

# 📥 Loading FTIR Data (CSV Format)

The FTIR instrument (or exported files) provides spectra like:

```

wavenumber,absorbance
4000,0.02
3950,0.02
...
1600,1.32
...

````

I created a dataset with:

- `reference_material.csv` — ground truth spectrum  
- `sample_good.csv` — within acceptable deviation  
- `sample_bad.csv` — clearly out-of-spec  
- `sample_new.csv` — realistic unknown material  

---

# 🧹 Preprocessing FTIR Spectra

Raw spectra often contain:

- Baseline shifts  
- Noise  
- Scaling inconsistencies  

This preprocessing pipeline ensures comparability:

```python
def advanced_preprocess(y):
    y = y - np.min(y)                      # baseline correction
    y = savgol_filter(y, 15, 3)           # smoothing
    return y / np.linalg.norm(y)          # normalization
````

---

# 📊 Visualizing Spectra

Here is an overlay of the processed spectra:

![FTIR spectrum comparison](/assets/img/ftir_erp/ftir_spectrum_comparison.png)

<small>Figure 2 — Normalized FTIR spectra for reference and samples.</small>

---

# 📐 PCA (Principal Component Analysis)

PCA compresses high-dimensional FTIR data into 2D for visualization:

![FTIR PCA clusters](/assets/img/ftir_erp/ftir_pca_clusters.png)

<small>Figure 3 — PCA projection revealing clusters of similar spectra.</small>

---

# 🧪 PASS/FAIL Logic Using RMS Error

A simple and effective QC metric is RMS difference from the reference:

```python
error = rms_error(reference, sample)
status = "PASS" if error <= 0.05 else "FAIL"
```

This produces output like:

```
sample_good.csv → PASS
sample_bad.csv → FAIL
sample_new.csv → PASS
```

---

# 🤖 Machine Learning Classifier (SVM)

For more advanced classification, I trained an SVM:

```python
clf = SVC(kernel="rbf", gamma="scale")
clf.fit(X_train, y_train)
prediction = clf.predict([new_spectrum])[0]
```

This allows:

* Multi-class classification
* Detection of subtle variation
* Improved generalization to new materials

---

# 🌐 Sending Results to ERP (FastAPI)

I built a mock ERP API:

```python
@app.post("/erp/ftir_report")
def receive_ftir_report(report: FTIRReport):
    print("ERP received QC report:")
    print(report)
```

And from the FTIR pipeline:

```python
payload = {
    "sample_name": "sample_new.csv",
    "rms_error": 0.034,
    "status": "PASS"
}
requests.post("http://127.0.0.1:8000/erp/ftir_report", json=payload)
```

ERP responds:

```
{"message": "Report stored in ERP", "received": true}
```

---

# 🚀 Results & Insights

This project demonstrates:

### ✓ FTIR spectra can be standardized, compared, and classified automatically

### ✓ PCA provides clear visual grouping of materials

### ✓ RMS or ML-based QC decisions reduce human error

### ✓ ERP integration enables real manufacturing automation

This workflow is suitable for:

* Polymer manufacturing
* Pharmaceuticals
* Chemical production
* Food quality labs
* Research environments

---

# 🧭 Future Work

Planned extensions include:

* Deep learning spectral classifiers
* Automated peak detection and chemical interpretation
* Integration with LIMS and MES systems
* Real-time dashboards inside ERP

---

# 📎 Project Files

* **Notebook:** `ftir.ipynb`
* **Python pipeline:** `code/ftir_erp_pipeline.py`
* **Mock ERP server:** `erp_mock_server.py`
* **Sample FTIR data:** `data/ftir_samples/`

---

# 💬 Final Thoughts

Bridging the gap between analytical instrumentation and enterprise systems is essential for modern Industry 4.0 workflows. FTIR spectroscopy is just the beginning — the same approach can be applied to Raman, NIR, UV-Vis, chromatography, and more.

If you want to learn more, check out the full project on GitHub or reach out with questions!

---

