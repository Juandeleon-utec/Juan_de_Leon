# Resumen del Proyecto — Rediseño Estructural de Cargador Rápido para Vehículos Eléctricos

**Curso:** Posgrado en Fabricación Digital
**Autor:** Juan Pedro de León
**Estado:** Borrador 3 con imágenes
**Última actualización:** 11-05-2026

---

## Resumen ejecutivo

El proyecto consistió en la reestructuración completa de un cargador rápido para vehículos eléctricos que presentaba fallas estructurales no recuperables mediante ajustes menores: problemas de transporte, ingreso de agua, dependencia de proveedores externos y un cambio de proveedor de fuentes de alimentación que obligó a replantear el layout interno. Se decidió abandonar la idea inicial de integrar un biorreactor de algas y enfocar el posgrado en un rediseño desde cero en Fusion 360, priorizando fabricabilidad, modularidad, robustez estructural y autonomía técnica respecto a terceros.

---

## Objetivos del rediseño

- Resolver problemas de transporte e instalación.
- Mejorar la resistencia a la intemperie.
- Reorganizar la estructura interna y corregir la carga estructural del gabinete.
- Diseñar bandejas específicas para la parte eléctrica/electrónica.
- Mejorar ventilación y vedación.
- Reducir dependencia de terceros mediante fabricación propia.
- Mantener continuidad estética con el modelo anterior.
- Adaptar el producto a nuevas configuraciones de potencia.

---

## Motivación

El prototipo original evidenció fallas estructurales y de proceso que no podían resolverse con parches: problemas de peso y carga del gabinete, ingreso de agua, dificultades de transporte, dependencia de proveedores sin control de diseño, cambio de proveedor de fuentes y baja disponibilidad de materiales certificados en el interior de Uruguay. Esto llevó a reiniciar el diseño priorizando fabricabilidad, modularidad y disponibilidad local de materiales y procesos.

---

## Decisiones técnicas clave

### Cambio de proveedor de fuentes de potencia
Se migró de **Phoenix Contact** (módulos CHARX PS-M2, 30 kW, ~27 kg c/u, fuerte dependencia de stock en Brasil) a **Maxwell** (módulo MXR100050B, 50 kW, ~23 kg c/u). La nueva plataforma permite configuraciones de 50/100/150 kW usando solo 3 fuentes en lugar de 4, reduciendo peso total instalado, mejorando ventilación interna, liberando espacio para reorganizar bandejas y facilitando mantenimiento.

### Sustitución del PLC y adecuación normativa
Se reemplazó el controlador previsto (Phoenix Contact EVPLC) por el **Vector vSECC.single**, alineado con estándares internacionales (IEC 61851) y con mejor integración de periféricos de seguridad. Se incorporó un **IMD (Insulation Monitoring Device)** para supervisar fallas de aislamiento en el bus DC de hasta 1000 VDC, y una **contactora principal DC de 400 A** que permite desenergizar las fuentes ante una falla sin perder el controlador, conservando capacidad de diagnóstico y registro de eventos.

### Monitoreo remoto y conectividad GSM
Se incorporó telemetría vía red móvil para un futuro dashboard centralizado, con variables como estado del cargador, alarmas, energía entregada, tiempo de carga y estado de comunicación con periféricos.

### Integración con Raspberry Pi
Mediante bus I2C, se sumó una Raspberry Pi con **PiSignage** y un servidor Apache/PHP local, para mostrar información operativa y contenido publicitario/institucional en la pantalla del equipo.

---

## Materiales y estructura

Se adoptó como referencia acero al carbono estructural equivalente a ASTM A36 / A500 / S235:

| Propiedad | Valor típico |
|---|---|
| Densidad | 7.85 g/cm³ |
| Módulo de elasticidad (E) | 200 GPa |
| Límite elástico (Fy) | 235–250 MPa |
| Resistencia última (Fu) | 370–550 MPa |

El despiece estructural (perfiles L, U, C y tubo cuadrado) totaliza aproximadamente **26.5 m de perfilería** y un **peso estructural estimado de ~44 kg**, valor considerado adecuado para equilibrar rigidez, transporte y carga sobre los anclajes.

---

## Análisis estructural de izaje (FEA — Fusion 360)

Como parte de la validación del soporte de izado de la estructura, se realizó un análisis de tensión estática en Fusion 360 sobre el caso de carga máxima de la familia de productos (configuración con 3 fuentes, que por dominancia estructural cubre el 100% de las variantes de venta).

**Metodología**

- Peso real total del cargador: 112 kg
- Factor de izaje aplicado: 1.5 (norma de equipos de izaje)
- Carga separada en dos vías: gravedad factorizada (14.71 m/s²) para el peso propio de la estructura modelada, y 4 fuerzas puntuales (350 N c/u) en los parantes verticales para los componentes no modelados (fuentes, cables, gabinete)
- Restricciones: 2 puntos fijos representando los anclajes de izaje
- Material: Acero AISI 1015 (límite de fluencia 285 MPa)

**Resultados**

| Parámetro | Valor |
|---|---|
| Factor de Seguridad mínimo | 2.253 |
| Rango objetivo | 2.0 – 4.0 |
| Tensión de von Mises máxima | 126.5 MPa |
| Desplazamiento máximo | 0.96 mm |
| Reacción punto de anclaje 1 | 832.0 N |
| Reacción punto de anclaje 2 | 832.4 N |

**Conclusión:** el Factor de Seguridad obtenido (2.25) cae dentro del rango objetivo, con un margen del 12.6% sobre el límite inferior. Las reacciones en ambos puntos de anclaje resultan prácticamente simétricas, validando la geometría de izaje propuesta. No se espera deformación permanente ni falla bajo la carga de diseño.

*El informe completo de la simulación (Fusion 360) se anexa por separado.*

---

## Dificultades encontradas

- El diseño original no era estructuralmente recuperable.
- Cambios sucesivos de proveedores obligaron a replantear decisiones internas durante todo el proyecto.
- Rehacer el listado completo de partes demandó más tiempo del previsto.
- Necesidad de adquirir nuevas competencias técnicas (soldadura MIG).
- Balancear continuidad estética con una reestructuración interna profunda.

---

## Resultados obtenidos

- Nuevo modelo estructural completo desarrollado en Fusion 360.
- Diseño más robusto, modular y mantenible.
- Mejor comportamiento frente a transporte e instalación, validado mediante análisis FEA de izaje.
- Mayor autonomía técnica: control total del modelo CAD para futuros ajustes ante cambios de proveedor.
- Adquisición de capacidad de fabricación propia (soldadura MIG).

---

## Estado actual y próximos pasos

Actualmente se están realizando las perforaciones del gabinete (ventilación, salida de cables, iluminación externa, soporte del conector CCS2 con LEDs WS2812B). La fabricación del primer prototipo, originalmente prevista para febrero de 2026, se reprogramó para mayo de 2026.

Próximos pasos: validar el diseño mediante fabricación real, ajustar detalles según pruebas físicas, documentar nuevas iteraciones e integrar los aprendizajes del proceso de soldadura.

---

## Referencias

- Cargador Phoenix Contact: [CHARX PS-M2 825DC/1000DC 30kW](https://www.phoenixcontact.com/pt-br/produtos/modulo-de-potencia-dc-charx-ps-m2-825dc-1000dc-30kw-1296467)
- Cargador Maxwell: [MXR100050B](https://www.maxwellpower.cn/productinfo/2413106.html)
- Norma IEC 61851: [UNIT](https://www.unit.org.uy/normalizacion/norma/100001554)
