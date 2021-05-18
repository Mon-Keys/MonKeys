CREATE TABLE client(  
    id SERIAL primary key,
    login varchar(255),
    email varchar(255),
    password varchar(255)   
);

CREATE TABLE company(  
    id SERIAL primary key,
    company_name VARCHAR(255) 
);

CREATE TABLE pass(  
    id SERIAL primary key,
    company_id int,
    client_id int,
    private_key varchar(255),
    CONSTRAINT fk_company_id
        FOREIGN KEY (company_id)
        REFERENCES company (id),
    CONSTRAINT fk_client_id
        FOREIGN KEY (client_id)
        REFERENCES client (id)
);

CREATE TABLE passage(  
    id SERIAL primary key,
    pass_id int,
    action_type SMALLINT,
    passage_time TIMESTAMP without time zone,
    CONSTRAINT fk_pass_id
        FOREIGN KEY (pass_id)
        REFERENCES pass (id)
);