FROM debian:buster-slim
RUN apt-get update -y && \
    apt-get install -y python-pip python-dev
COPY ./requirements.txt /app/requirements.txt
WORKDIR /app
RUN pip install -r requirements.txt
ADD . /app/
EXPOSE 80
ENTRYPOINT [ "python" ]
CMD [ "app.py" ]