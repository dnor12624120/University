package Domain;

import Domain.Entities.Client;

import static org.junit.jupiter.api.Assertions.*;

class ClientTest {

    @org.junit.jupiter.api.Test
    void getName() {
        String clientName = "name";
        int clientAge = 20;
        Client client = new Client(clientName, clientAge);
        assertEquals("name", client.getName());
    }

    @org.junit.jupiter.api.Test
    void getAge() {
        String clientName = "name";
        int clientAge = 20;
        Client client = new Client(clientName, clientAge);
        assertEquals(20, client.getAge());
    }

    @org.junit.jupiter.api.Test
    void setName() {
        Client client = new Client("", 20);
        client.setName("name");
        assertEquals("name", client.getName());
    }

    @org.junit.jupiter.api.Test
    void setAge() {
        Client client = new Client("", 0);
        client.setAge(20);
        assertEquals(20, client.getAge());
    }
}