package Repository;

import Domain.Entities.BaseEntity;
import Domain.Validators.Validator;
import Domain.Validators.ValidatorException;
import Utility.Utility;
import Utility.Sort;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;
import java.util.Optional;
import java.util.function.Supplier;

public class XMLRepository<ID extends Serializable, T extends BaseEntity<ID>> extends InMemoryRepository<ID, T> implements SortingRepository<ID, T> {
    private String filepath;
    private Supplier<? extends T> constructor;


    public XMLRepository(String filepath, Validator<T> validator, Supplier<? extends T> constructor) throws ParserConfigurationException, SAXException, IOException, TransformerException
    {
        super(validator);
        this.filepath = filepath;
        this.constructor = constructor;
        loadFromFile();
    }

    private Document getDocument() throws ParserConfigurationException, IOException, SAXException
    {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setIgnoringComments(true);
        factory.setIgnoringElementContentWhitespace(true);
        factory.setValidating(false);

        DocumentBuilder builder = factory.newDocumentBuilder();
        return builder.parse(new InputSource(filepath));
    }

    private void loadFromFile() throws IOException, SAXException, ParserConfigurationException, TransformerException
    {
        if(!Utility.isFileEmpty(filepath))
        {
            Document document = getDocument();
            T tempInstance = constructor.get();

            NodeList entities = document.getElementsByTagName(tempInstance.getEntityTag());

            for (int i = 0; i < entities.getLength(); i++)
            {
                Element element = (Element) entities.item(i);
                T entity = constructor.get();
                entity.initializeFromXMLElement(element);
                super.save(entity);
            }
        }
    }

    private void saveToFile() throws IOException, ParserConfigurationException, SAXException, TransformerException
    {
        Utility.clearContentsOfFile(filepath);
        Utility.createBlankXMLTemplate(filepath);
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        Document document = getDocument();
        Element root = document.getDocumentElement();
        super.entities.values().forEach(entity -> entity.appendXMLContentToDocument(document, root));
        transformer.transform(new DOMSource(document), new StreamResult(new File(filepath)));
    }

    public Optional<T> save(T entity) throws ValidatorException, IOException, TransformerException, SAXException, ParserConfigurationException
    {
        Optional<T> result = super.save(entity);
        saveToFile();
        return result;
    }

    @Override
    public Optional<T> delete(ID id) throws IOException, TransformerException, SAXException, ParserConfigurationException
    {
        Optional<T> result = super.delete(id);
        saveToFile();
        return result;
    }

    @Override
    public Optional<T> update(T entity) throws ValidatorException, IOException, TransformerException, SAXException, ParserConfigurationException
    {
        Optional<T> result = super.update(entity);
        saveToFile();
        return result;
    }

    @Override
    public Iterable<T> findAll(Sort sort)
    {
        return null;
    }
}
