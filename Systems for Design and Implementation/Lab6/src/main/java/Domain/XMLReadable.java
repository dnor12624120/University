package Domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public interface XMLReadable
{
    void initializeFromXMLElement(Element element);
    void appendXMLContentToDocument(Document document, Element root);
}
