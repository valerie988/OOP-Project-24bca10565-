#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// 🔹 Base Class: Document
class Document
{
protected:
    string fileName;
    int numPages;

public:
    Document(string name = "Untitled", int pages = 0)
        : fileName(name), numPages(pages) {}

    virtual void displayInfo() const
    {
        cout << "Document Name: " << fileName << endl;
        cout << "Number of Pages: " << numPages << endl;
    }

    virtual string getName() const
    {
        return fileName;
    }

    virtual int getPages() const
    {
        return numPages;
    }

    virtual ~Document()
    {
        // Virtual destructor for base class
    }
};

// 🔹 Derived Class: PDFDocument
class PDFDocument : public Document
{
private:
    string author;
    string creationDate;

    string getCurrentDate() const
    {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
        return string(buf);
    }

public:
    PDFDocument(string name, int pages, string auth)
        : Document(name, pages), author(auth)
    {
        creationDate = getCurrentDate();
    }

    void displayInfo() const override
    {
        cout << "\n📄 PDF Document Info" << endl;
        cout << "-----------------------------" << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << numPages << endl;
        cout << "Created On: " << creationDate << endl;
    }

    string getAuthor() const
    {
        return author;
    }

    string getDate() const
    {
        return creationDate;
    }
};

// 🔹 PDF Merger Class
class PDFMerger
{
private:
    vector<PDFDocument> pdfList;
    string mergedFileName;

public:
    PDFMerger(string outputFile = "Merged_Output.pdf")
        : mergedFileName(outputFile) {}

    void addDocument(const PDFDocument &pdf)
    {
        pdfList.push_back(pdf);
        cout << "✅ Added: " << pdf.getName() << " (" << pdf.getPages() << " pages)\n";
    }

    void showDocuments() const
    {
        cout << "\n📚 Documents in Merge Queue" << endl;
        cout << "-----------------------------" << endl;
        if (pdfList.empty())
        {
            cout << "No PDF files added yet.\n";
            return;
        }
        for (size_t i = 0; i < pdfList.size(); ++i)
        {
            cout << i + 1 << ". " << pdfList[i].getName()
                 << " — " << pdfList[i].getPages() << " pages" << endl;
        }
    }

    void mergePDFs()
    {
        if (pdfList.size() < 2)
        {
            cout << "⚠️ Need at least 2 PDF files to merge.\n";
            return;
        }

        ofstream mergedFile(mergedFileName);
        if (!mergedFile)
        {
            cerr << "❌ Error creating merged PDF file.\n";
            return;
        }

        mergedFile << "Merged PDF Document\n";
        mergedFile << "-----------------------------\n";

        int totalPages = 0;
        for (const auto &pdf : pdfList)
        {
            mergedFile << "Included: " << pdf.getName()
                       << " (" << pdf.getPages() << " pages)\n";
            totalPages += pdf.getPages();
        }

        mergedFile << "-----------------------------\n";
        mergedFile << "Total Pages in Merged File: " << totalPages << "\n";
        mergedFile.close();

        cout << "\n✅ Successfully merged " << pdfList.size()
             << " files into '" << mergedFileName << "' (" << totalPages << " pages total)\n";
    }

    void clearList()
    {
        pdfList.clear();
        cout << "🗑 Cleared all added PDF files from queue.\n";
    }
};

// 🔹 Main Program
int main()
{
    cout << "==============================" << endl;
    cout << "  PDF Document Merge Tool" << endl;
    cout << "==============================" << endl;

    PDFMerger merger("MergedProjectOutput.pdf");

    // Creating PDF documents (you can modify these)
    PDFDocument pdf1("Assignment1.pdf", 10, "Alice");
    PDFDocument pdf2("Report2025.pdf", 15, "Bob");
    PDFDocument pdf3("ThesisIntro.pdf", 12, "Charlie");

    // Add PDFs to merger
    merger.addDocument(pdf1);
    merger.addDocument(pdf2);
    merger.addDocument(pdf3);

    // Display info
    merger.showDocuments();

    // Merge PDFs
    merger.mergePDFs();

    // Display individual PDF details
    cout << "\n-----------------------------\n";
    cout << "📘 Individual PDF Details:\n";
    pdf1.displayInfo();
    pdf2.displayInfo();
    pdf3.displayInfo();

    cout << "\n🎯 Program completed successfully.\n";
    return 0;
}
