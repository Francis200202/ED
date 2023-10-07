/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "packet_processor.hpp"


PacketProcessor::PacketProcessor(size_t size):
    _max_size(size),
    _finish_time()
{}

Response PacketProcessor::process(const Packet &packet)
{
    Response ret (true, 0); //Default is to drop the packet.
    //TODO
    //First: deque all processed packets at packet time arrival.
    //Saque de la cola todos los paquetes procesados en el momento de la llegada del paquete.
    //En _finish_time se almacenan los paq procesados
    int time = 0;
    //Si finish_time no esta vacio
    if(_finish_time.is_empty()==false){
        //y ha llegado
        if(packet.arrival_time>=_finish_time.front()){
            _finish_time.deque();
        }
    }
    //
    //Second: Is there any place for this packet in the queue?
    //¿Hay algún lugar en la cola para este paquete?
    if (_finish_time.size()>=_max_size)
    {
    //This packet will be processed after the last packet is processed and
    //its completion time will be 'package processing time' later time units.
    //Remember that the queue saves the finish processing time for the packets.
    //Remember to update the returned response.
        //
    //Este paquete se procesará después de que se procese el último paquete y su tiempo 
    //de finalización será 'tiempo de procesamiento del paquete' unidades de 
    //tiempo posteriores.
     //Recuerde que la cola guarda el tiempo de procesamiento final de los paquetes.
     //Recuerde actualizar la respuesta devuelta.
        return ret;
    //
    }
    if(_finish_time.is_empty()){
        time = packet.arrival_time;
    }
    else{
        time = _finish_time.back();
    }
    _finish_time.enque(time+packet.process_time);
    ret.dropped=false;
    ret.start_time=time;
    return ret;
}


/** @brief process the packets and generate a response for each of them.*/
std::vector <Response>
process_packets(const std::vector <Packet> &packets,
                PacketProcessor& p)
{
    std::vector <Response> responses;
    for (size_t i = 0; i < packets.size(); ++i)
    {
        responses.push_back(p.process(packets[i]));
    }
    return responses;
}

/** @brief print the processing start times for the packets.*/
std::ostream&
write_responses(std::ostream &out, const std::vector <Response> &responses)
{
    for (size_t i = 0; i < responses.size(); ++i)
        out << (responses[i].dropped ? -1 : responses[i].start_time)
            << std::endl;
    return out;
}
